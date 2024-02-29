#pragma once

#include "function.h"

#include <vector>
#include <iostream>

struct AIGNode {
    unsigned left;
    bool negate_left;
    unsigned right;
    bool negate_right;
    AIGNode();
    AIGNode(unsigned left, bool negate_left, unsigned right, bool negate_right);
};

class AIG {
    unsigned variable_count;
    unsigned output;
    bool negate_output;
    std::vector<AIGNode> nodes;

    bool traverse(const std::vector<bool> &x, unsigned v, std::vector<unsigned> &used) const;
    bool traverse_cycles(unsigned v, std::vector<unsigned> &used) const;
public:
    AIG();
    ~AIG();

    unsigned getVariableCount() const;
    void setVariableCount(unsigned count);

    unsigned getOutput() const;
    void setOutput(unsigned vertex);
    
    bool getNegateOutput() const;
    void setNegateOutput(bool value);

    std::vector<AIGNode> &getNodes();
    const std::vector<AIGNode> &getNodes() const;
    unsigned addNode(const AIGNode &node);
    
    bool hasCycles() const;

    unsigned getComplexity() const;
    Function getFunction() const;

    void read(std::istream &istream);
    void print(std::ostream &ostream) const;
};

