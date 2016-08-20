`timescale 1ns / 1ps

module RegisterFile_Test;

	// Inputs
	reg clk;
	reg we;
	reg [1:0] read_addr1;
	reg [1:0] read_addr2;
	reg [1:0] write_addr;
	reg [7:0] write_data;

	// Outputs
	wire [7:0] read_data1;
	wire [7:0] read_data2;

	// Instantiate the Unit Under Test (UUT)
	RegisterFile uut (
		.clk(clk), 
		.we(we), 
		.read_addr1(read_addr1), 
		.read_addr2(read_addr2), 
		.write_addr(write_addr), 
		.write_data(write_data), 
		.read_data1(read_data1), 
		.read_data2(read_data2)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		we = 0;
		read_addr1 = 0;
		read_addr2 = 0;
		write_addr = 0;
		write_data = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		we = 1;
		write_addr = 2'd0;
		write_data = 8'd4;
		
		#100
		we = 1;
		write_addr = 2'd1;
		write_data = 8'd12;
		
		#100
		we = 0;
		read_addr1 = 2'd0;
		read_addr2 = 2'd1;
	end
	
	always
	begin
		#100
		clk = !clk;
	end
endmodule

