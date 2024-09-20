`timescale 1ns/10ps

module multiplier_tb;
	reg [2:0] A, B;
    wire [5:0] P;

	multiplier uut(A, B, P);

	initial begin
		for (integer a = 0; a < 8; a++) begin
			for (integer b = 0; b < 8; b++) begin
				#10 A = a; B = b;
			end
		end
	end

	// Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!

endmodule
