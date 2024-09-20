`timescale 1ns / 1ps

module machine_d_tb;
    reg x, CLK, RESET;
    wire F;
    wire[2:0] S;

    machine_d uut(x, CLK, RESET, F, S);

    initial begin
        $dumpfile("test.vcd");
        $dumpvars();
        
        x = 0; CLK = 0; RESET = 1;
        #5 x = 0; CLK = 0; RESET = 0;
        #4 x = 1; CLK = 1; RESET = 0;

        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;

        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;

        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;

        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;

        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;

        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;
        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        
        #10 x = 0; CLK = 1; RESET = 0;
        #10 x = 0; CLK = 0; RESET = 0;

        #10 x = 1; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 1;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;

        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;
        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 1;
        #10 x = 0; CLK = 0; RESET = 0;
        #10 x = 0; CLK = 1; RESET = 0;
        #10 x = 1; CLK = 0; RESET = 0;
        #10 x = 1; CLK = 1; RESET = 0;
    end
    // Your code goes here.  DO NOT change anything that is already given! Otherwise, you will not be able to pass the tests!
endmodule