module Asic_Miner (
	input			               CLOCK_50,
	input	           [0:0]		KEY,
	
	//////////// SDRAM //////////
	output		    [12:0]		DRAM_ADDR,
	output		     [1:0]		DRAM_BA,
	output		          		DRAM_CAS_N,
	output		          		DRAM_CKE,
	output		          		DRAM_CLK,
	output		          		DRAM_CS_N,
	inout 		    [15:0]		DRAM_DQ,
	output		          		DRAM_LDQM,
	output		          		DRAM_RAS_N,
	output		          		DRAM_UDQM,
	output		          		DRAM_WE_N
	
);

wire    CLOCK_SHA;

system nios_system (
	.sys_clk_clk   (CLOCK_50),    
  // .sha_clk_clk   (CLOCK_SHA),	
	.reset_reset_n	(KEY[0]),
	.sdram_wire_addr                (DRAM_ADDR),                //              sdram_wire.addr
	.sdram_wire_ba                  (DRAM_BA),                  //                        .ba
	.sdram_wire_cas_n               (DRAM_CAS_N),               //                        .cas_n
	.sdram_wire_cke                 (DRAM_CKE),                 //                        .cke
	.sdram_wire_cs_n                (DRAM_CS_N),                //                        .cs_n
	.sdram_wire_dq                  (DRAM_DQ),                  //                        .dq
	.sdram_wire_dqm                 ({DRAM_UDQM,DRAM_LDQM}),    //                        .dqm
	.sdram_wire_ras_n               (DRAM_RAS_N),               //                        .ras_n
	.sdram_wire_we_n                (DRAM_WE_N)                 //                        .we_n
);




endmodule
