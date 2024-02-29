#include "ig.h"
#include "ig_bruteforce.h"
#include "ig_lupanov.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ranges>

std::ofstream file;

using namespace std;


IG build_pdnf(Function function) {
    IG dnf;
    auto variable_count = function.getVariableCount();
    dnf.setVariableCount(variable_count);
    const auto truth_table = function.getTruthTable();
 
    std::vector<int> nodes_to_dnf;
 
 
    // compute all conjuctions
    for (int bitset = 0; bitset < (1 << variable_count); ++bitset) {
 
        // if function is 1 -> take all positive nodes and connect
 
        if (!truth_table[bitset]) continue;
 
        for (int pos = 0; pos < variable_count; ++pos) {
            bool negate = (bitset >> pos) & 1;
 
            if (pos == 0) {
                dnf.addNode(IGNode({1, 1}, {negate, negate}, {0, 0, 0, 1}));
            } else {
                auto last = dnf.getLastNodeNum();
                dnf.addNode(IGNode({last, pos + 1}, {negate, 0}, {0, 0, 0, 1}));
            }
        }
 
        nodes_to_dnf.push_back(dnf.getLastNodeNum());
    }
 
    if (nodes_to_dnf.size() == 0) {
        dnf.addNode(IGNode({1, 1}, {1, 0}, {0, 0, 0, 1})); // all 0 function
        dnf.setOutput(dnf.getLastNodeNum());
        return dnf;
    }
 
    if (nodes_to_dnf.size() == 1) {
        dnf.setOutput(dnf.getLastNodeNum());
        return dnf;
    }
 
    for (int i = 1; i < nodes_to_dnf.size(); ++i) {
        if (i == 1) {
            dnf.addNode(IGNode({nodes_to_dnf[0], nodes_to_dnf[1]}, {1, 1}, {0, 0, 0, 1}));
        } else {
            dnf.addNode(IGNode({dnf.getLastNodeNum(), nodes_to_dnf[i]}, {0, 1}, {0, 0, 0, 1}));
        }
    }
 
    dnf.setOutput(dnf.getLastNodeNum());
    return dnf;
}
int main(int argc, char* argv[]) {
    // IG test;

    // test.setVariableCount(5);

    // std::ifstream inputFile("./src/input.txt");
    // if (inputFile.is_open()) {
    //     test.read(inputFile);
    //     inputFile.close();
    // } else {
    //     std::cout << "ERROR OPENING FILE!\n";
    //     return 0;
    // }

    // test.print(std::cout);

    // auto f = test.getResult();
    // f.print(std::cout);
    // // f.bigPrint(std::cout);

    // IG test;
    // test.setVariableCount(2);
    // test.addFunction(Function({0,0,0,1}));
    // IGBruteforcer bruteforce_test;
    // bruteforce_test.bruteforce(test, 2);

    // file.open("output.txt", std::ios::out);

    // IG aig_test;
    // aig_test.setVariableCount(3);
    // aig_test.addFunction(Function({0,0,0,1}));
    // IGBruteforcer bruteforce_aig_test;
    // bruteforce_aig_test.bruteforce(aig_test, 4);


    // IG xaig_test;
    // xaig_test.setVariableCount(4);
    // xaig_test.addFunction(Function({0,0,0,1}));
    // xaig_test.addFunction(Function({0,1,1,0}));
    // IGBruteforcer bruteforce_xaig_test;
    // bruteforce_xaig_test.bruteforce(xaig_test, 5);

    // Function f(5);
    // f.setValue(std::vector<bool> (8, true), true); // f - conjuction;
    // IGLupanov test_lupanov(f);




    
    


    if (argc > 2) {
        std::cerr << "WRONG USAGE!\n";
        return 0;
    }

    if (argc == 2) {
        std::string func = argv[1];
        std::vector<bool> func_vector(func.size());
        for (auto [s_val, v_val] : std::views::zip(func, func_vector)) {
            v_val = s_val == '1';
        }
        Function f(func_vector);
        IGLupanov test_lupanov(f);
        test_lupanov.synthesis();
        return 0;
    }

    std::ifstream inputFile("/Users/michaelbrown/Documents/GitHub/aig_project/src/input.txt");
    std::string func;
    inputFile >> func;
    std::vector<bool> func_vector(func.size());
    for (auto [s_val, v_val] : std::views::zip(func, func_vector)) {
        v_val = s_val == '1';
    }
    Function f(func_vector);
        IGLupanov test_lupanov(f);
    test_lupanov.synthesis();
    //auto res_aig = build_pdnf(f);
    //res_aig.MKSprint(std::cout);
    // IGLupanov test_lupanov(Function({1,0,0,1,0,1,1,1}));
    // IGLupanov test_lupanov(Function({1,0,0,1,0,1,1,1,
    //                                  1,0,1,1,0,0,0,1,
    //                                  1,0,0,0,0,1,0,1,
    //                                  0,0,1,1,0,1,0,1}));


    return 0;
}
