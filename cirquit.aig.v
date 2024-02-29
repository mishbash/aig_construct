// Benchmark "example" written by ABC on Fri Oct  6 22:47:17 2023

module example ( 
    x1, x2, x3,
    z  );
  input  x1, x2, x3;
  output z;
  wire new_n5;
  assign new_n5 = ~x1 & x2;
  assign z = ~x3 | ~new_n5;
endmodule


