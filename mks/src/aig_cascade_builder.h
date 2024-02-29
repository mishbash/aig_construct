#pragma once

#include "aig.h"
#include "variable_order.h"

#include <map>

class AIGCascadeBuilder {
    bool check_aig(const AIG &aig, const Function &function) const;
    std::pair<Function, Function> split(const Function &function, unsigned variable) const;
    std::pair<unsigned, bool> cascade_node(AIG &aig, const Function &function,
        const VariableOrder &variable_order, unsigned priority,
        std::map<Function, std::pair<unsigned, bool>> &nodemap) const;
    AIG build_with_order(const Function &function,
        const VariableOrder &variable_order) const;
public:
    AIGCascadeBuilder();
    ~AIGCascadeBuilder();
    AIG build(const Function &function) const;
};
