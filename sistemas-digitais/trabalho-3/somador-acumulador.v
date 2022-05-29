module somador(
	input clk,
	input [7:0] a,
	input [7:0] b,
	input r,
	output [7:0] s
);


	reg [7:0] s_reg;
	assign s = s_reg;

always @(posedge clk) begin
	if (r)begin
		s_reg <= 0;
	end else begin
		s_reg <= s_reg+(a*b);
	end
end
endmodule



module teste;
	reg clk;
	reg [7:0] a, b;
	reg r;
	wire [7:0] s;

always #2 clk = ~clk;

	somador A(clk, a, b, r, s);

initial begin
	$dumpvars(0, A);
	#0 clk <= 0;
	r <= 1;
	a <= 1;
	b <= 1;
	#2
	r <= 0;
	#10 
	a <= 4;
	b <= 5;
	#10 
	a <= 2;
	b <= 3;
	#50;
	$finish;
end

endmodule
