module example (x1, x2, x3, z);
    input x1, x2, x3;
    output z;
    wire x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22;
    assign x4 =  x1 &  x1;
    assign x5 = ~x4 &  x2;
    assign x6 =  x5 &  x3;
    assign x7 = ~x1 & ~x1;
    assign x8 = ~x7 &  x2;
    assign x9 =  x8 &  x3;
    assign x10 =  x1 &  x1;
    assign x11 =  x10 &  x2;
    assign x12 = ~x11 &  x3;
    assign x13 = ~x1 & ~x1;
    assign x14 =  x13 &  x2;
    assign x15 = ~x14 &  x3;
    assign x16 = ~x1 & ~x1;
    assign x17 = ~x16 &  x2;
    assign x18 = ~x17 &  x3;
    assign x19 = ~x6 & ~x9;
    assign x20 =  x19 & ~x12;
    assign x21 =  x20 & ~x15;
    assign x22 =  x21 & ~x18;
    assign z =  x22;
    
endmodule

