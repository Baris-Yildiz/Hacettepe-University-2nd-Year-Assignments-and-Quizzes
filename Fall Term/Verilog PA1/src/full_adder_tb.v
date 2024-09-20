`timescale 1ns/10ps

module full_adder_tb;

    reg A, B, Cin;
    wire S, Cout;

    full_adder uut(A, B, Cin, S, Cout);

    initial begin
        #10 A = 0; B = 0; Cin = 0;
        #10 A = 0; B = 0; Cin = 1;
        #10 A = 0; B = 1; Cin = 0;
        #10 A = 0; B = 1; Cin = 1;
        #10 A = 1; B = 0; Cin = 0;
        #10 A = 1; B = 0; Cin = 1;
        #10 A = 1; B = 1; Cin = 0;
        #10 A = 1; B = 1; Cin = 1;
    end
    // Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!
endmodule
