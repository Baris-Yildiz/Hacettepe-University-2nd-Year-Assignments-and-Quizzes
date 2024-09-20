`timescale 1us / 1ps

module ECSU(
    input CLK,
    input RST,
    input thunderstorm,
    input [5:0] wind,
    input [1:0] visibility,
    input signed [7:0] temperature,
    output reg severe_weather,
    output reg emergency_landing_alert,
    output reg [1:0] ECSU_state
);

integer signed_temperature = 0;

always @* begin
    if (temperature[7]) begin
        signed_temperature = (~temperature +1)*-1;
    end else begin
        signed_temperature = temperature;
    end

    if(thunderstorm | (wind > 15) | (signed_temperature > 35) | (signed_temperature < -35) | visibility == 2'b11) begin
        severe_weather = 1;
    end else if (thunderstorm | (wind > 15) | (signed_temperature < -35) | (signed_temperature > 35) | visibility == 2'b11) begin
        severe_weather = 1;
    end else if ((!thunderstorm) & (wind <= 10) & ((signed_temperature >= -35) & (signed_temperature <= 35)) & visibility == 2'b01) begin
        severe_weather = 0;
    end

    if ((signed_temperature < -40) | (signed_temperature > 40) | wind > 20) begin
        emergency_landing_alert = 1;
    end
end

always @(posedge CLK, posedge RST) begin
    if (RST) begin
        ECSU_state = 2'b00;  //reset to all-clear
        severe_weather = 0;
        emergency_landing_alert = 0;
    end else begin
        case (ECSU_state)
            2'b00: begin
                if ((wind <= 15 & wind > 10) | visibility == 2'b01) begin
                    ECSU_state = 2'b01;  
                end else if(severe_weather) begin
                    ECSU_state = 2'b10;
                end
            end
            2'b01: begin
                if (wind <= 10 & visibility == 2'b00) begin
                    ECSU_state = 2'b00;
                end else if (severe_weather) begin
                    ECSU_state = 2'b10;
                end
            end
            2'b10: begin
                if (emergency_landing_alert) begin
                    ECSU_state = 2'b11;
                end else if (!severe_weather) begin
                    ECSU_state = 2'b01;
                end
            end
        endcase
    end
end

// Your code goes here.

endmodule