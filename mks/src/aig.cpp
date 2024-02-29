#include "aig.h"

AIGNode::AIGNode() : left(0), negate_left(false), right(0), negate_right(false) {}

AIGNode::AIGNode(unsigned left, bool negate_left, unsigned right,
    bool negate_right) : left(left), negate_left(negate_left), right(right),
    negate_right(negate_right) {}

AIG::AIG() : variable_count(5), output(0), negate_output(false), nodes() {}

AIG::~AIG() {}

unsigned AIG::getVariableCount() const {
    return variable_count;
}

void AIG::setVariableCount(unsigned count) {
    variable_count = count;
}

unsigned AIG::getOutput() const {
    return output;
}

void AIG::setOutput(unsigned vertex) {
    output = vertex;
}

bool AIG::getNegateOutput() const {
    return negate_output;
}

void AIG::setNegateOutput(bool value) {
    negate_output = value;
}

std::vector<AIGNode> &AIG::getNodes() {
    return nodes;
}

const std::vector<AIGNode> &AIG::getNodes() const {
    return nodes;
}

unsigned AIG::addNode(const AIGNode &node) {
    nodes.push_back(node);
    return nodes.size() + variable_count;
}

bool AIG::hasCycles() const {
    std::vector<unsigned> used(nodes.size());
    return traverse_cycles(output, used);
}

unsigned AIG::getComplexity() const {
    return nodes.size();
}

bool AIG::traverse(const std::vector<bool> &x, unsigned v, std::vector<unsigned> &used) const {
    if ((v >= 1) && (v <= variable_count)) {
        return !x[v - 1];
    }
    v -= variable_count + 1;
    if (used[v]) {
        return used[v] == 2;
    }
    const AIGNode &node = nodes.at(v);
    bool left = traverse(x, node.left, used) ^ node.negate_left;
    bool right = traverse(x, node.right, used) ^ node.negate_right;
    used[v] = (left && right) ? 2 : 1;
    return used[v] == 2;
}

bool AIG::traverse_cycles(unsigned v, std::vector<unsigned> &used) const {
    if ((v >= 1) &&(v <= variable_count)) {
        return false;
    }
    v -= variable_count + 1;
    used[v] = 1;
    const AIGNode &node = nodes.at(v);
    if ((node.left > variable_count) && (used[node.left - variable_count - 1] == 1)) {
        return true;
    }
    if ((node.right > variable_count) && (used[node.right - variable_count - 1] == 1)) {
        return true;
    }
    if ((node.left > variable_count) && !used[node.left - variable_count - 1]) {
        if (traverse_cycles(node.left, used)) {
            return true;
        }
    }
    if ((node.right > variable_count) && !used[node.right - variable_count - 1]) {
        if (traverse_cycles(node.right, used)) {
            return true;
        }
    }
    used[v] = 2;
    return false;
}

Function AIG::getFunction() const {
    std::vector<bool> x(variable_count, false);
    Function f(variable_count);
    for (unsigned i = 0; i < (1 << variable_count); ++i) {
        std::vector<unsigned> used(nodes.size(), 0);
        bool value = traverse(x, output, used) ^ negate_output;
        f.setValue(x, value);
        for (int j = (variable_count - 1); j >= 0; --j) {
            x[j] = !x[j];
            if (x[j]) {
                break;
            }
        }
    }
    return f;
}

void AIG::read(std::istream &istream) {
    nodes.clear();
    unsigned cmplx;
    istream >> cmplx >> output >> negate_output;
    for (unsigned i = 0; i < cmplx; ++i) {
        AIGNode node;
        istream >> node.left >> node.negate_left >> node.right >> node.negate_right;
        nodes.push_back(node);
    }
}

void AIG::print(std::ostream &ostream) const {
    ostream << getComplexity() << " ";
    ostream << output << " " << (negate_output ? 1 : 0) << " ";
    for (auto &c : nodes) {
        ostream << c.left << " " << (c.negate_left ? 1 : 0) << " " <<
            c.right << " " << (c.negate_right ? 1 : 0) << " ";
    }
    ostream << std::endl;
}

