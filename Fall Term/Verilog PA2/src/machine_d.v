module machine_d(
    input wire x,
    input wire CLK,
    input wire RESET,
    output wire F,
    output wire [2:0] S
);
    //A(t+1) = A + Bx';
    //B(t+1) = B'x' + Bx + Ax';
    //C(t+1) = C'x + Cx';

    wire W1,W2,W3,W4,W5,W6,W7,W8,W9; // intermediate wires.
    wire A,B,C; //state variables

    and G5(W1, B, ~x);
    or G6(W2, A, W1);   

    and G7(W3, B, x);
    and G8(W4, ~B, ~x);
    and G9(W5, A, ~x);
    or G10(W6,W3,W4,W5);

    and G11(W7,~C,x);
    and G12(W8,C,~x); 
    or G13(W9,W7,W8);

    and(F,A,B,~C);

    dff dff1(W2, CLK, RESET, A);
    dff dff2(W6, CLK, RESET, B);
    dff dff3(W9, CLK, RESET, C);

    assign S = {A,B,C};
    // Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!
endmodule