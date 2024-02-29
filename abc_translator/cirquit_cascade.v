module example (x1, x2, x3, x4, z);
    input x1, x2, x3, x4;
    output z;
    wire x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16;
    assign x5 =  x3 &  x4;
    assign x6 = ~x5 &  x3;
    assign x7 =  x1 & ~x6;
    assign x8 =  x3 &  x4;
    assign x9 =  x2 &  x8;
    assign x10 =  x3 & ~x4;
    assign x11 = ~x3 &  x4;
    assign x12 = ~x10 & ~x11;
    assign x13 = ~x2 & ~x12;
    assign x14 = ~x9 & ~x13;
    assign x15 = ~x1 & ~x14;
    assign x16 = ~x7 & ~x15;
    assign z = ~x16;
    
endmodule

