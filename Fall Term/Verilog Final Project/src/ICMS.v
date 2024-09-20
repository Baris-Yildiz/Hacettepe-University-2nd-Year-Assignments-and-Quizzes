`timescale 1us / 1ps

module ICMS(
    input CLK,
    input RST,

    input radar_echo,
    input scan_for_target,
    input [31:0] jet_speed,
    input [31:0] max_safe_distance,
    input [5:0] wind,
    input thunderstorm,
    input [1:0] visibility,
    input signed [7:0] temperature,

    output radar_pulse_trigger,
    output [31:0] distance_to_target,
    output safe_to_engage,
    output threat_detected,
    output emergency_landing_alert,
    output [1:0] ECSU_state,  
    output [1:0] ARTAU_state
);

    wire severe_weather;
    ARTAU artau_unit(radar_echo,scan_for_target,jet_speed,max_safe_distance,
                    RST,CLK,radar_pulse_trigger,distance_to_target,threat_detected,ARTAU_state);

    ECSU ecsu_unit(CLK,RST,thunderstorm,wind,visibility,temperature,
                    severe_weather,emergency_landing_alert,ECSU_state);

    and(safe_to_engage,threat_detected,~severe_weather);

   // Your code goes here.
    

endmodule