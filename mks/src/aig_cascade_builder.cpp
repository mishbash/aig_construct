#include "aig_cascade_builder.h"

AIGCascadeBuilder::AIGCascadeBuilder() {}

AIGCascadeBuilder::~AIGCascadeBuilder() {}

bool AIGCascadeBuilder::check_aig(const AIG &aig, const Function &function) const {
    return (aig.getComplexity() > 0) && (aig.getFunction() == function);
}

std::pair<Function, Function> AIGCascadeBuilder::split(
    const Function &function, unsigned variable) const {
    Function a = function;
    Function b = function;
    unsigned variable_count = function.getVariableCount();
    std::vector<bool> x(variable_count, false);
    std::vector<bool> y;
    for (unsigned i = 0; i < (1 << variable_count); ++i) {
        if (x[variable]) {
            y = x;
            y[variable] = false;
            a.setValue(x, a.getValue(y));
        } else {
            y = x;
            y[variable] = true;
            b.setValue(x, b.getValue(y));
        }
        for (int j = x.size() - 1; j >= 0; --j) {
            x[j] = !x[j];
            if (x[j]) {
                break;
            }
        }
    }
    return std::make_pair(a, b);
}

std::pair<unsigned, bool> AIGCascadeBuilder::cascade_node(AIG &aig,
    const Function &function,
    const VariableOrder &variable_order, unsigned priority,
    std::map<Function, std::pair<unsigned, bool>> &nodemap) const {
    if (nodemap.count(function)) {
        return nodemap[function];
    }
    unsigned variable = variable_order.getOrder()[priority];
    std::pair<Function, Function> splitted =
        split(function, variable);
    Function a = splitted.first;
    Function b = splitted.second;
    if ((a == function) || (b == function)) {
        return cascade_node(aig, function, variable_order, priority + 1, nodemap);
    }
    Function zero = Function(function.getVariableCount(), false);
    Function one = Function(function.getVariableCount(), true);
    std::pair<unsigned, bool> left_node = std::make_pair(0, false);
    if (!(a == zero)) {
        if (a == one) {
            left_node = std::make_pair(variable + 1, false);
        } else {
            auto f_node = cascade_node(aig, a, variable_order, priority + 1, nodemap);
            AIGNode var_node(variable + 1, false, f_node.first, f_node.second);
            left_node = std::make_pair(aig.addNode(var_node), false);
        }
    }
    std::pair<unsigned, bool> right_node = std::make_pair(0, false);
    if (!(b == zero)) {
        if (b == one) {
            right_node = std::make_pair(variable + 1, true);
        } else {
            auto f_node = cascade_node(aig, b, variable_order, priority + 1, nodemap);
            AIGNode var_node(variable + 1, true, f_node.first, f_node.second);
            right_node = std::make_pair(aig.addNode(var_node), false);
        }
    }
    if (left_node.first == 0) {
        nodemap[function] = right_node;
        return right_node;
    }
    if (right_node.first == 0) {
        nodemap[function] = left_node;
        return left_node;
    }
    AIGNode aig_node(left_node.first, left_node.second ^ true,
        right_node.first, right_node.second ^ true);
    return nodemap[function] = std::make_pair(aig.addNode(aig_node), true);
}

AIG AIGCascadeBuilder::build_with_order(const Function &function,
    const VariableOrder &variable_order) const {
    AIG result;
    result.setVariableCount(function.getVariableCount());
    std::map<Function, std::pair<unsigned, bool>> nodemap;
    auto node = cascade_node(result, function, variable_order, 0, nodemap);
    result.setOutput(node.first);
    result.setNegateOutput(node.second);
    return result;
}

AIG AIGCascadeBuilder::build(const Function &function) const {
    VariableOrder variable_order(function.getVariableCount());
    AIG result;
    result.setVariableCount(function.getVariableCount());
    unsigned result_complexity = 0;
//    for (unsigned i = 0; i < variable_order.permutations(); ++i) {
        AIG aig = build_with_order(function, variable_order);
        if (check_aig(aig, function)) {
            unsigned cur_complexity = aig.getComplexity();
            if ((result_complexity == 0) ||
                (cur_complexity < result_complexity)) {
                result = aig;
                result_complexity = cur_complexity;
            }
        }
//        variable_order.nextPermutation();
//    }
    return result;
}


