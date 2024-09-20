`timescale 1us / 1ps

module ARTAU(
    input radar_echo,
    input scan_for_target,
    input [31:0] jet_speed,
    input [31:0] max_safe_distance,
    input RST,
    input CLK,
    output reg radar_pulse_trigger,
    output reg [31:0] distance_to_target,
    output reg threat_detected,
    output reg [1:0] ARTAU_state
);

real start_time, end_time, t = 0;
real c0 = 3 * (10 **8);
integer pulse_count = 0;
reg listening = 0;
reg detected = 0;
integer d1, counter, result,t1 = 0;

always @(posedge scan_for_target, posedge radar_echo) begin
    if (scan_for_target) begin
        radar_pulse_trigger = 1;  
        #300;
        radar_pulse_trigger = 0;
        start_time = $time;
    end
     
    if (radar_echo) begin
        if (listening) begin
            t = $time - start_time;
            distance_to_target = (c0 * t) / (2 * (10 ** 6)); 
            detected = 1;

            if (!d1) begin
                d1 = distance_to_target;
                t1 = t;
                radar_pulse_trigger = 1;
                #300;
                radar_pulse_trigger = 0;
                start_time = $time;
                
            end else begin
                result = ((distance_to_target + (jet_speed * t1 * (10**(-6)))) - d1);

                if ((result < 0) & (distance_to_target < max_safe_distance)) begin
                    threat_detected = 1;
                end
            end
            
        end
    end
end


always @(posedge CLK, posedge RST) begin
    
    if (RST) begin
        ARTAU_state <= 2'b00;
        radar_pulse_trigger = 0;
        threat_detected = 0;
        distance_to_target = 32'd0;
        pulse_count = 0;
        listening = 0;
        detected = 0;
        d1 = 32'd0;
        counter = 32'd0;
    end 

    if (ARTAU_state == 2'b00) begin
        threat_detected = 0;
        distance_to_target = 32'd0;
        pulse_count = 0;
        listening = 0;
        counter = 32'd0;
        d1 = 32'd0;
        detected = 0;
        if (radar_pulse_trigger) begin
            ARTAU_state <= 2'b01;
            #300;
            listening = 1;
            pulse_count++;
        end
    end

    if (ARTAU_state == 2'b01) begin
        ARTAU_state <= 2'b10;  
    end

    if (ARTAU_state == 2'b10) begin
        while (!detected & counter < 2000) begin
            counter++;
            #1;
        end
        listening = 0;
        counter = 32'd0;
        detected = 0;
        if (t) begin
            if (pulse_count == 1) begin
                t = 0;
                ARTAU_state <= 2'b01; 
                #300;
                
                listening = 1;
                pulse_count++; 
            end else begin
                ARTAU_state <= 2'b11;
            end
        end else begin
            ARTAU_state <= 2'b00;
        end
    end

    if (ARTAU_state == 2'b11) begin
        while (!radar_pulse_trigger & counter < 3000) begin
            counter++;
            #1;
        end
        counter = 0;
            if (radar_pulse_trigger) begin
                ARTAU_state <= 2'b01;
                d1 = 32'd0;
                t=0;
                detected = 0;
                pulse_count = 1;
                #300;
                start_time = $time;
                listening = 1;
                radar_pulse_trigger = 0;
            end else begin
                ARTAU_state <= 2'b00;
                threat_detected = 0;
                distance_to_target = 0;
            end
    end
end


endmodule