module Leds(
	input [1:0] KEY,
	input CLOCK_50,
	output [0:0] LEDG
);
	
	reg [26:0] counter;
	reg state;
	assign LEDG[0] = state;
	
always @(posedge CLOCK_50) begin
	
	if (KEY[0] == 0) begin
		counter <= counter + 1;
		state <= counter[26];
	end
		
	else if (KEY[1] == 0) begin
		counter <= counter + 1;
		state <= counter[22]; 
	end
end

endmodule
