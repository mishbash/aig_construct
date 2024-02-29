module example (x1, x2, x3, z);
    input x1, x2, x3;
    output z;
    wire x4;
    assign x4 = ~x2 & ~x3;
    assign z =  x4;
    
endmodule

