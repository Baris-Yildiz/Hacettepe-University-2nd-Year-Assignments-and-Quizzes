`timescale 1ns/10ps

module half_adder_tb;

	reg A, B;
	wire S, C;

	half_adder uut(A, B, S, C);

	initial begin
		#10 A = 0; B = 0;
		#10 A = 0; B = 1;
		#10 A = 1; B = 0;
		#10 A = 1; B = 1;
	end

	// Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!

endmodule
