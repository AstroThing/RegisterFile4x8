`timescale 1ns / 1ps

module Main(
		input clk,
		input we,
		input [1:0] read_addr1,
		input [1:0] read_addr2,
		input [1:0] write_addr,
		input [7:0] write_data,
		output [7:0] read_data1,
		output [7:0] read_data2
    );

	RegisterFile rf(clk, we, read_addr1, read_addr2, write_addr, write_data, read_data1, read_data2);

endmodule
