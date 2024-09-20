`timescale 1ns/10ps

module half_adder(
    input A, B,
    output S, C
);

    assign S = A ^ B;
    assign C = A & B;

	// Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!

endmodule
