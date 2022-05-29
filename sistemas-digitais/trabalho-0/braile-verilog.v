module T0_Braille(
	input [0:5] SW,
	input CLOCK_50,

	output reg [0:7] HEX0,
	output reg [0:7] HEX1,
	output reg [0:7] HEX2,
	output reg [0:7] HEX3
);

	always @(posedge CLOCK_50) begin
	

		if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 0 && SW[4] == 0 && SW[5] == 0 ) begin // A
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 1 && SW[3] == 0 && SW[4] == 0 && SW[5] == 0 ) begin // B
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 0 && SW[4] == 0 && SW[5] == 0 ) begin // C
		
			HEX0[0] <= 0;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 1 && SW[4] == 0 && SW[5] == 0 ) begin // D
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 0;
			
		end
		
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 1 && SW[4] == 0 && SW[5] == 0 ) begin // E
		
			HEX0[0] <= 0;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 1 && SW[3] == 0 && SW[4] == 0 && SW[5] == 0 ) begin // F
		
			HEX0[0] <= 0;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 1 && SW[3] == 1 && SW[4] == 0 && SW[5] == 0 ) begin // G
		
			HEX0[0] <= 0;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 1 && SW[3] == 1 && SW[4] == 0 && SW[5] == 0 ) begin // H
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 0 && SW[1] == 1 && SW[2] == 1 && SW[3] == 0 && SW[4] == 0 && SW[5] == 0 ) begin // I
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 1;
			HEX0[5] <= 1;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 0 && SW[1] == 1 && SW[2] == 1 && SW[3] == 1 && SW[4] == 0 && SW[5] == 0 ) begin // J
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 0 && SW[4] == 1 && SW[5] == 0 ) begin // K  	|_|
																																			//			|
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 1;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 1 && SW[3] == 0 && SW[4] == 1 && SW[5] == 0 ) begin // L
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 0 && SW[4] == 1 && SW[5] == 0 ) begin // M		 _
																																			//			| |
			HEX0[0] <= 0;																												//			| |
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 1 && SW[4] == 1 && SW[5] == 0 ) begin // N
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 1 && SW[4] == 1 && SW[5] == 0 ) begin // O
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 1 && SW[3] == 0 && SW[4] == 1 && SW[5] == 0 ) begin // P
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 1;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 1 && SW[3] == 1 && SW[4] == 1 && SW[5] == 0 ) begin // Q
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 1;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 1 && SW[3] == 1 && SW[4] == 1 && SW[5] == 0 ) begin // R
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 0 && SW[1] == 1 && SW[2] == 1 && SW[3] == 0 && SW[4] == 1 && SW[5] == 0 ) begin // S
		
			HEX0[0] <= 0;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 1;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 0 && SW[1] == 1 && SW[2] == 1 && SW[3] == 1 && SW[4] == 1 && SW[5] == 0 ) begin // T
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 1;
			HEX0[5] <= 1;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 0 && SW[4] == 1 && SW[5] == 1 ) begin // U
		
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 1 && SW[3] == 0 && SW[4] == 1 && SW[5] == 1 ) begin // V
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 1;
			
		end
		else if ( SW[0] == 0 && SW[1] == 1 && SW[2] == 1 && SW[3] == 1 && SW[4] == 0 && SW[5] == 1 ) begin // W
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 0 && SW[4] == 1 && SW[5] == 1 ) begin // X
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 0;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 1 && SW[2] == 0 && SW[3] == 1 && SW[4] == 1 && SW[5] == 1 ) begin // Y
		
			HEX0[0] <= 1;
			HEX0[1] <= 0;
			HEX0[2] <= 0;
			HEX0[3] <= 1;
			HEX0[4] <= 1;
			HEX0[5] <= 0;
			HEX0[6] <= 0;
			
		end
		else if ( SW[0] == 1 && SW[1] == 0 && SW[2] == 0 && SW[3] == 1 && SW[4] == 1 && SW[5] == 1 ) begin // Z
		
			HEX0[0] <= 0;
			HEX0[1] <= 0;
			HEX0[2] <= 1;
			HEX0[3] <= 0;
			HEX0[4] <= 0;
			HEX0[5] <= 1;
			HEX0[6] <= 0;
			
		end
		
		else begin   //todos apagados
			HEX0[0] <= 1;
			HEX0[1] <= 1;
			HEX0[2] <= 1;
			HEX0[3] <= 1;
			HEX0[4] <= 1;
			HEX0[5] <= 1;
			HEX0[6] <= 1;
			
			HEX1[0] <= 1;
			HEX1[1] <= 1;
			HEX1[2] <= 1;
			HEX1[3] <= 1;
			HEX1[4] <= 1;
			HEX1[5] <= 1;
			HEX1[6] <= 1;
			
			HEX2[0] <= 1;
			HEX2[1] <= 1;
			HEX2[2] <= 1;
			HEX2[3] <= 1;
			HEX2[4] <= 1;
			HEX2[5] <= 1;
			HEX2[6] <= 1;
			
			HEX3[0] <= 1;
			HEX3[1] <= 1;
			HEX3[2] <= 1;
			HEX3[3] <= 1;
			HEX3[4] <= 1;
			HEX3[5] <= 1;
			HEX3[6] <= 1;
		end
	
	end

endmodule
