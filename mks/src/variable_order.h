#pragma once

#include <vector>
#include <map>

class VariableOrder {
    unsigned variable_count;
    std::vector<unsigned> order;
    std::map<unsigned, unsigned> priority;
public:
    VariableOrder(unsigned variable_count);
    ~VariableOrder();
    
    std::vector<unsigned> getOrder() const;
    unsigned permutations() const;
    void nextPermutation();
    unsigned getPriority(unsigned variable) const;
};

