module piscaledsajustavel(

	input [0:2] KEY,
	input CLOCK_50,
	output reg [7:0] LEDG
);

reg d;
reg temp_botao;
reg [25:0] s;
reg [25:0] cont;





always @(posedge CLOCK_50) begin

	if (KEY[0] == 0) begin
		s <= 0;
		d <= 0;
		LEDG <= 1;
		cont <= 11000000;
	end
	

	else begin

		if (s == cont) begin
		
			if (KEY[2] == 0) begin
				if (cont > 700000) begin
					cont <= cont - 100000;
				end
			end
			if (KEY[1] == 0) begin
				if (cont < 11000000) begin
					cont <= cont + 100000;
				end
			end

		
			if (d == 0) begin
				LEDG <= LEDG * 2;
			end
						
			else begin
				LEDG <= LEDG / 2;
			end
			
			if (LEDG[6] == 1) d<=1;
				else if (LEDG[1] == 1) d<=0;
					s <= 0;
				end 

			else begin
				s <= s + 1;
			end

		end
		
	
	end

endmodule