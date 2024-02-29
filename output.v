module example

    parameter VAR_COUNT  = 25597929,
              NODE_COUNT = 33


    input  [VAR_COUNT:1] x,
    output               z


    wire [VAR_COUNT+NODE_COUNT:1] nodes;
    assign nodes[VAR_COUNT:1] = x[VAR_COUNT:1];
    assign z = ~nodes[0];
    assign nodes[25597930] = ~nodes[0] &  nodes[2];
    assign nodes[25597931] = ~nodes[0] & ~nodes[2];
    assign nodes[25597932] = ~nodes[0] & ~nodes[1];
    assign nodes[25597933] = ~nodes[1] & ~nodes[5];
    assign nodes[25597934] = ~nodes[1] &  nodes[5];
    assign nodes[25597935] = ~nodes[1] & ~nodes[5];
    assign nodes[25597936] = ~nodes[1] &  nodes[5];
    assign nodes[25597937] = ~nodes[1] &  nodes[5];
    assign nodes[25597938] = ~nodes[1] & ~nodes[5];
    assign nodes[25597939] = ~nodes[1] & ~nodes[5];
    assign nodes[25597940] = ~nodes[1] & ~nodes[4];
    assign nodes[25597941] = ~nodes[1] & ~nodes[5];
    assign nodes[25597942] = ~nodes[1] &  nodes[5];
    assign nodes[25597943] = ~nodes[1] &  nodes[4];
    assign nodes[25597944] = ~nodes[1] &  nodes[5];
    assign nodes[25597945] = ~nodes[2] & ~nodes[3];
    assign nodes[25597946] = ~nodes[2] & ~nodes[1];
    assign nodes[25597947] = ~nodes[3] & ~nodes[4];
    assign nodes[25597948] = ~nodes[5] &  nodes[3];
    assign nodes[25597949] = ~nodes[5] &  nodes[1];
    assign nodes[25597950] = ~nodes[5] & ~nodes[1];
    assign nodes[25597951] = ~nodes[6] &  nodes[4];
    assign nodes[25597952] = ~nodes[8] & ~nodes[3];
    assign nodes[25597953] = ~nodes[9] &  nodes[4];
    assign nodes[25597954] = ~nodes[9] & ~nodes[4];
    assign nodes[25597955] = ~nodes[12] &  nodes[3];
    assign nodes[25597956] = ~nodes[12] & ~nodes[3];
    assign nodes[25597957] = ~nodes[13] &  nodes[4];
    assign nodes[25597958] = ~nodes[15] & ~nodes[4];
    assign nodes[25597959] = ~nodes[15] & ~nodes[3];
    assign nodes[25597960] = ~nodes[18] & ~nodes[4];
    assign nodes[25597961] = ~nodes[20] &  nodes[3];
    assign nodes[25597962] = ~nodes[20] &  nodes[4];
    
endmodule

