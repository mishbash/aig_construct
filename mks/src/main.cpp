#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <ranges>

#include "aig_cascade_builder.h"

int main(int argc, char **argv) {
    
    std::ifstream inputFile("/Users/michaelbrown/Documents/GitHub/aig_project/src/input.txt");
    std::string func;
    inputFile >> func;
    std::vector<bool> func_vector(func.size());
    for (auto [s_val, v_val] : std::views::zip(func, func_vector)) {
        v_val = s_val == '1';
    }
    Function f(func_vector);

    AIGCascadeBuilder test_cascade_builder;
    auto test_res = test_cascade_builder.build(f);
    test_res.print(std::cout);

    return 0;
}
