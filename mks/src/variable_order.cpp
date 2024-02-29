#include "variable_order.h"
#include <algorithm>

VariableOrder::VariableOrder(unsigned variable_count) :
    variable_count(variable_count), order(variable_count), priority() {
    for (unsigned i = 0; i < variable_count; ++i) {
        order[i] = i;
        priority[i] = i;
    }
}

VariableOrder::~VariableOrder() {}

std::vector<unsigned> VariableOrder::getOrder() const {
    return order;
}

unsigned VariableOrder::permutations() const {
    unsigned result = 1;
    for (unsigned i = 2; i <= variable_count; ++i) {
        result *= i;
    }
    return result;
}

void VariableOrder::nextPermutation() {
    std::next_permutation(order.begin(), order.end());
    priority.clear();
    for (unsigned i = 0; i < variable_count; ++i) {
        priority[order[i]] = i;
    }
}

unsigned VariableOrder::getPriority(unsigned variable) const {
    return priority.at(variable);
}

