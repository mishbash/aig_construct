#! /usr/bin/python3

import sys

template = '''module {} ({}, z);
    input {};
    output z;
    wire {};
    {}
    assign z = {}x{};
    
endmodule
'''

def aig2verilog(module_name, aig_str, skip=False):
    var_count, node_count, out_node, out_inv, *aig_code = [int(v) for v in aig_str.split()][skip:]
    verilog_code_list = []
    for k in range(node_count):
        left_node, left_inv, right_node, right_inv = aig_code[4*k : 4*(k+1)]
        left_prefix = '~' if left_inv else ' '
        right_prefix = '~' if right_inv else ' '
        verilog_code_list.append(
            f'assign x{k + var_count + 1} = {left_prefix}x{left_node} & {right_prefix}x{right_node};')
    varlist = ', '.join(f'x{k}' for k in range(1, var_count + 1))
    nodelist = ', '.join(f'x{k}' for k in range(var_count + 1, var_count + node_count + 1))
    out_prefix = '~' if out_inv else ' '
    return template.format(module_name, varlist, varlist, nodelist,
                    '\n    '.join(verilog_code_list), out_prefix, out_node)

def main():
    module_name, in_file_name, out_file_name = sys.argv[1:]
    with open(in_file_name, 'r') as in_file:
        aig_str = in_file.read()
    with open(out_file_name, 'w') as out_file:
        print(aig2verilog(module_name, aig_str), file=out_file)

main()
