#include "function.h"

Function::Function() : variable_count(0), truth_table() {}

Function::Function(unsigned variable_count) : variable_count(variable_count),
    truth_table(1 << variable_count, false) {}

Function::Function(unsigned variable_count, bool value) :
    variable_count(variable_count), truth_table(1 << variable_count, value) {}

Function::Function(const std::vector<bool> &truth_table) :
    variable_count(0), truth_table(truth_table) {
    while ((1 << variable_count) < truth_table.size()) {
        ++variable_count;
    }
}

Function::~Function() {}

bool Function::operator()(const std::vector<bool> &x) const {
    return getValue(x);
}

bool Function::operator==(const Function &function) const {
    return truth_table == function.getTruthTable();
}

bool Function::operator!=(const Function &function) const {
    return truth_table != function.getTruthTable();
}

bool Function::operator<(const Function &function) const {
    for (size_t i = 0; i < truth_table.size(); ++i) {
        if (truth_table[i] < function.getTruthTable()[i]) {
            return true;
        }
        if (truth_table[i] > function.getTruthTable()[i]) {
            return false;
        }
    }
    return false;
}

Function Function::operator~() const {
    std::vector<bool> new_truth_table(truth_table.size());
    for (size_t i = 0; i < truth_table.size(); ++i) {
        new_truth_table[i] = !truth_table[i];
    }
    return Function(new_truth_table);
}

Function Function::operator&(const Function &function) const {
    std::vector<bool> new_truth_table(truth_table.size());
    for (size_t i = 0; i < truth_table.size(); ++i) {
        new_truth_table[i] = truth_table[i] & function.getTruthTable()[i];
    }
    return Function(new_truth_table);
}

unsigned Function::getVariableCount() const {
    return variable_count;
}

const std::vector<bool> &Function::getTruthTable() const {
    return truth_table;
}

bool Function::getValue(const std::vector<bool> &x) const {
    unsigned table_index = 0;
    for (unsigned i = 0; i < x.size(); ++i) {
        table_index = (table_index << 1) + (x[i] ? 1 : 0);
    }
    return truth_table[table_index];
}

void Function::setValue(const std::vector<bool> &x, bool value) {
    unsigned table_index = 0;
    for (unsigned i = 0; i < x.size(); ++i) {
        table_index = (table_index << 1) + (x[i] ? 1 : 0);
    }
    truth_table[table_index] = value;
}

unsigned Function::mincode() const {
    unsigned result = 0;
    for (unsigned i = 0; i < truth_table.size(); ++i) {
        result = (result << 1) + (truth_table[i] ? 1 : 0);
    }
    return result;
}

Function Function::reordered(const VariableOrder &variable_order, const std::vector<bool> &neg_flags) const {
    std::vector<bool> new_table(truth_table.size(), false);
    std::vector<bool> x(variable_count, false);
    std::vector<bool> y(variable_count);
    for (std::size_t i = 0; i < new_table.size(); ++i) {
        unsigned place = 0;
        for (unsigned j = 0; j < variable_count; ++j) {
            y[variable_order.getOrder()[j]] = (x[j] ^ neg_flags[j]);
        }
        for (unsigned j = 0; j < variable_count; ++j) {
            place = 2 * place + y[j];
        }
        new_table[i] = truth_table[place];
        for (int j = variable_count - 1; j >= 0; --j) {
            x[j] = !x[j];
            if (x[j]) {
                break;
            }
        }
    }
    return Function(new_table);
}

std::pair<VariableOrder, std::vector<bool>> Function::minorder(unsigned fixed_variable) const {
    VariableOrder variable_order(variable_count);
    VariableOrder result = variable_order;
    std::vector<bool> result_nf(variable_count, false);
    unsigned result_mincode = mincode();
    for (unsigned i = 0; i < variable_order.permutations(); ++i) {
        if (variable_order.getOrder().back() == fixed_variable) {
            std::vector<bool> neg_flags(variable_count, false);
            for (std::size_t j = 0; j < truth_table.size(); ++j) {
                unsigned current_mincode = reordered(variable_order, neg_flags).mincode();
                if (current_mincode < result_mincode) {
                    result_mincode = current_mincode;
                    result_nf = neg_flags;
                    result = variable_order;
                }
                for (int l = variable_count - 1; l >= 0; --l) {
                    neg_flags[l] = !neg_flags[l];
                    if (neg_flags[l]) {
                        break;
                    }
                }
            }
        }
        variable_order.nextPermutation();
    }
    return std::make_pair(result, result_nf);
}

std::pair<VariableOrder, std::vector<bool>> Function::minorder() const {
    VariableOrder result(variable_count);
    std::vector<bool> result_nf(variable_count, false);
    unsigned result_mincode = mincode();
    for (unsigned i = 0; i < variable_count; ++i) {
        auto p = minorder(i);
        unsigned current_mincode = reordered(p.first, p.second).mincode();
        if (current_mincode < result_mincode) {
            result_mincode = current_mincode;
            result_nf = p.second;
            result = p.first;
        }
    }
    return std::make_pair(result, result_nf);
}

std::vector<Function> Function::getInverseCongruentClass(bool can_negate_output) const {
    std::vector<Function> result;
    VariableOrder variable_order(variable_count);
    for (unsigned i = 0; i < variable_order.permutations(); ++i) {
        std::vector<bool> neg_flags(variable_count, false);
        for (std::size_t j = 0; j < truth_table.size(); ++j) {
            result.push_back(reordered(variable_order, neg_flags));
            if (can_negate_output) {
                result.push_back(~result.back());
            }
            for (int l = variable_count - 1; l >= 0; --l) {
                neg_flags[l] = !neg_flags[l];
                if (neg_flags[l]) {
                    break;
                }
            }
        }
        variable_order.nextPermutation();
    }
    return result;
}

bool Function::isZero() const {
    for (const auto &i : truth_table) {
        if (i) {
            return false;
        }
    }
    return true;
}

void Function::print(std::ostream &ostream) const {
    for (unsigned i = 0; i < truth_table.size(); ++i) {
        ostream << truth_table[i];
    }
    ostream << std::endl;
}
