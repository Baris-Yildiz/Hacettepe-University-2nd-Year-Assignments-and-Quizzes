`timescale 1ns/10ps

module full_adder(
    input A, B, Cin,
    output S, Cout
);

    wire S1, C1;
    half_adder HA1(A, B, S1, C1);

    wire C2;
    half_adder HA2(S1, Cin, S, C2);

    or(Cout, C2, C1);

	// Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!

endmodule
