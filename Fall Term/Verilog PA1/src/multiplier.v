`timescale 1ns/10ps

module multiplier (
    input [2:0] A, B,
    output [5:0] P
);

    wire [2:0] IntermediateCarries;

    and (P[0], B[0], A[0]);

    wire a1b0, a0b1;
    and(a1b0, A[1], B[0]);
    and(a0b1, A[0], B[1]);

    half_adder HA1(a1b0, a0b1, P[1], IntermediateCarries[0]);

    wire [2:0] Intermediate;

    wire a2b0, a1b1;
    
    and(a2b0, A[2], B[0]);
    and(a1b1, A[1], B[1]);

    full_adder FA1(a2b0, a1b1, IntermediateCarries[0], Intermediate[0], IntermediateCarries[1]);

    wire a2b1;
    and(a2b1, A[2], B[1]);

    half_adder HA2(a2b1, IntermediateCarries[1], Intermediate[1], IntermediateCarries[2]);

    assign Intermediate[2] = IntermediateCarries[2];

    wire[2:0] Carries;

    wire a0b2;
    and(a0b2, A[0], B[2]);
    half_adder HA3(a0b2, Intermediate[0], P[2], Carries[0]);

    wire a1b2;
    and(a1b2, A[1], B[2]);
    full_adder FA2(a1b2, Intermediate[1], Carries[0], P[3], Carries[1]);

    wire a2b2;
    and(a2b2, A[2], B[2]);
    full_adder FA3(a2b2, Intermediate[2], Carries[1], P[4], Carries[2]);

    assign P[5] = Carries[2];

	// Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!


endmodule
