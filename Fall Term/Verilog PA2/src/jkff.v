module jkff (
    input J,      // Data input
    input K,      // Data input
    input CLK,    // Clock input
    input RESET,  // Asynchronous reset, active high
    output reg Q  // Output
);

    always @(posedge CLK, posedge RESET) begin
        if (RESET) begin
            Q <= 0;
        end else if (J && K) begin
            Q <= ~Q;
        end else if (J) begin
            Q <= 0;
        end else if (K) begin
            Q <= 1;
        end
    end
    // Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!
endmodule