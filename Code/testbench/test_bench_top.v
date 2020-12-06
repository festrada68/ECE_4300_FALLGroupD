
`timescale 1ns / 10ps

module test;
reg		clk;
reg		rst;

reg		kld;
reg	[127:0]	key;
reg	[127:0]	text_in;


wire	[127:0]	cypher_text;
wire		done;

aes_cipher_top u0(
	.clk(		clk		),
	.rst(		rst		),
	.ld(		kld		),
	.done(		done		),
	.key(		key		),
	.text_in(	text_in		),
	.cypher_text(	cypher_text	)
	);

initial clk = 1'b0;
always #5 clk = ~clk;

initial begin
rst = 1'b0;
kld = 1'b0;
repeat(4)	@(posedge clk);
rst = 1;
repeat(18)	@(posedge clk);
//#1 rst = 1'b0;

#1 kld = 1'b1;
key = 128'h00000000000000000000000000000000;

text_in = 128'hFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
#20 kld = 1'b0;
repeat(12) @(posedge clk);
kld = 1'b1;
#10;
kld = 1'b0;
//key = 128'hx;

//text_in = 128'hx;
end
//ANSWER = 3f5b8cc9ea855a0afa7347d23e8d664e
endmodule
