module example (x1, x2, x3, z);
    input x1, x2, x3;
    output z;
    wire x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28;
    assign x4 =  x1 &  x1;
    assign x5 = ~x1 & ~x1;
    assign x6 =  x4 &  x2;
    assign x7 =  x5 &  x2;
    assign x8 =  x4 & ~x2;
    assign x9 =  x5 & ~x2;
    assign x10 =  x3 &  x3;
    assign x11 = ~x3 & ~x3;
    assign x12 =  x6 &  x6;
    assign x13 = ~x12 & ~x8;
    assign x14 = ~x13 & ~x13;
    assign x15 = ~x14 & ~x9;
    assign x16 = ~x15 & ~x15;
    assign x17 =  x16 &  x10;
    assign x18 =  x17 &  x17;
    assign x19 =  x6 &  x6;
    assign x20 = ~x19 & ~x7;
    assign x21 = ~x20 & ~x20;
    assign x22 = ~x21 & ~x8;
    assign x23 = ~x22 & ~x22;
    assign x24 = ~x23 & ~x9;
    assign x25 = ~x24 & ~x24;
    assign x26 =  x25 &  x11;
    assign x27 = ~x18 & ~x26;
    assign x28 = ~x27 & ~x27;
    assign z =  x28;
    
endmodule

