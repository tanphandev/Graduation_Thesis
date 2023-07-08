`timescale 1ns/1ps
`default_nettype none

module tb_sha256();

  //----------------------------------------------------------------
  // Internal constant and parameter definitions.
  //----------------------------------------------------------------
  parameter DEBUG = 0;

  parameter CLK_HALF_PERIOD = 5;
  parameter CLK_PERIOD = 2 * CLK_HALF_PERIOD;

  // The address map.
  parameter ADDR_NAME0       = 8'h00;
  parameter ADDR_NAME1       = 8'h01;
  parameter ADDR_VERSION     = 8'h02;

  parameter ADDR_CTRL        = 8'h08;
  parameter CTRL_INIT_VALUE  = 8'h01;
  parameter CTRL_NEXT_VALUE  = 8'h02;
  parameter CTRL_MODE_VALUE  = 8'h04;
  parameter CTRL_IRQ_EN_VALUE  = 8'h08;

  parameter ADDR_STATUS      = 8'h09;
  parameter STATUS_READY_BIT = 0;
  parameter STATUS_VALID_BIT = 1;

  parameter ADDR_BLOCK0    = 8'h10;
  parameter ADDR_BLOCK1    = 8'h11;
  parameter ADDR_BLOCK2    = 8'h12;
  parameter ADDR_BLOCK3    = 8'h13;
  parameter ADDR_BLOCK4    = 8'h14;
  parameter ADDR_BLOCK5    = 8'h15;
  parameter ADDR_BLOCK6    = 8'h16;
  parameter ADDR_BLOCK7    = 8'h17;
  parameter ADDR_BLOCK8    = 8'h18;
  parameter ADDR_BLOCK9    = 8'h19;
  parameter ADDR_BLOCK10   = 8'h1a;
  parameter ADDR_BLOCK11   = 8'h1b;
  parameter ADDR_BLOCK12   = 8'h1c;
  parameter ADDR_BLOCK13   = 8'h1d;
  parameter ADDR_BLOCK14   = 8'h1e;
  parameter ADDR_BLOCK15   = 8'h1f;

  parameter ADDR_DIGEST0   = 8'h20;
  parameter ADDR_DIGEST1   = 8'h21;
  parameter ADDR_DIGEST2   = 8'h22;
  parameter ADDR_DIGEST3   = 8'h23;
  parameter ADDR_DIGEST4   = 8'h24;
  parameter ADDR_DIGEST5   = 8'h25;
  parameter ADDR_DIGEST6   = 8'h26;
  parameter ADDR_DIGEST7   = 8'h27;
  
  parameter ADDR_IRQ_CLR   = 8'h28;
  parameter IRQ_CLR        = 8'h01;

  parameter SHA224_MODE    = 0;
  parameter SHA256_MODE    = 1;


  //----------------------------------------------------------------
  // Register and Wire declarations.
  //----------------------------------------------------------------
  reg [31 : 0] cycle_ctr;
  reg [31 : 0] error_ctr;
  reg [31 : 0] tc_ctr;

  reg           tb_clk;
  reg           tb_reset_n;
  reg           tb_cs;
  reg           tb_we;
  reg [7 : 0]   tb_address;
  reg [31 : 0]  tb_write_data;
  wire [31 : 0] tb_read_data;
  wire          tb_irq;

  reg [31 : 0]  read_data;
  reg [255 : 0] digest_data;
  reg [255 : 0] reverse_digest;
  reg [255 : 0] target;

  //----------------------------------------------------------------
  // Device Under Test.
  //----------------------------------------------------------------
  sha256 dut(
             .clk(tb_clk),
             .reset_n(tb_reset_n),

             .cs(tb_cs),
             .we(tb_we),


             .address(tb_address),
             .write_data(tb_write_data),
             .read_data(tb_read_data),
             .irq(tb_irq)
            );


  //----------------------------------------------------------------
  // clk_gen
  //
  // Clock generator process.
  //----------------------------------------------------------------
  always
    begin : clk_gen
      #CLK_HALF_PERIOD tb_clk = !tb_clk;
    end // clk_gen


  //----------------------------------------------------------------
  // sys_monitor
  //
  // Generates a cycle counter and displays information about
  // the dut as needed.
  //----------------------------------------------------------------
  always
    begin : sys_monitor
      #(2 * CLK_HALF_PERIOD);
      cycle_ctr = cycle_ctr + 1;
    end


  //----------------------------------------------------------------
  // dump_dut_state()
  //
  // Dump the state of the dump when needed.
  //----------------------------------------------------------------
  task dump_dut_state;
    begin
      $display("State of DUT");
      $display("------------");
      $display("Inputs and outputs:");
      $display("cs = 0x%01x, we = 0x%01x",
               dut.cs, dut.we);
      $display("address = 0x%02x", dut.address);
      $display("write_data = 0x%08x, read_data = 0x%08x",
               dut.write_data, dut.read_data);
      $display("tmp_read_data = 0x%08x", dut.tmp_read_data);
      $display("");

      $display("Control and status:");
      $display("ctrl = 0x%02x, status = 0x%02x",
               {dut.next_reg, dut.init_reg},
               {dut.digest_valid_reg, dut.ready_reg});
      $display("");

      $display("Message block:");
      $display("block0  = 0x%08x, block1  = 0x%08x, block2  = 0x%08x,  block3  = 0x%08x",
               dut.block_reg[00], dut.block_reg[01], dut.block_reg[02], dut.block_reg[03]);
//      $display("block4  = 0x%08x, block5  = 0x%08x, block6  = 0x%08x,  block7  = 0x%08x",
//               dut.block_reg[04], dut.block_reg[05], dut.block_reg[06], dut.block_reg[07]);

      $display("block8  = 0x%08x, block9  = 0x%08x, block10 = 0x%08x,  block11 = 0x%08x",
               dut.block_reg[08], dut.block_reg[09], dut.block_reg[10], dut.block_reg[11]);
      $display("block12 = 0x%08x, block13 = 0x%08x, block14 = 0x%08x,  block15 = 0x%08x",
               dut.block_reg[12], dut.block_reg[13], dut.block_reg[14], dut.block_reg[15]);
      $display("");

      $display("Digest:");
      $display("digest = 0x%064x", dut.digest_reg);
      $display("");

    end
  endtask // dump_dut_state


  //----------------------------------------------------------------
  // reset_dut()
  //
  // Toggles reset to force the DUT into a well defined state.
  //----------------------------------------------------------------
  task reset_dut;
    begin
      $display("*** Toggle reset.");
      tb_reset_n = 0;
      #(4 * CLK_HALF_PERIOD);
      tb_reset_n = 1;
    end
  endtask // reset_dut


  //----------------------------------------------------------------
  // init_sim()
  //
  // Initialize all counters and testbed functionality as well
  // as setting the DUT inputs to defined values.
  //----------------------------------------------------------------
  task init_sim;
    begin
      cycle_ctr = 32'h0;
      error_ctr = 32'h0;
      tc_ctr = 32'h1;

      tb_clk = 0;
      tb_reset_n = 0;
      tb_cs = 0;
      tb_we = 0;
      tb_address = 6'h0;
      tb_write_data = 32'h0;
    end
  endtask // init_dut


  //----------------------------------------------------------------
  // display_test_result()
  //
  // Display the accumulated test results.
  //----------------------------------------------------------------
  task display_test_result;
    begin
      if (error_ctr == 0)
        begin
          $display("*** All %02d test cases completed successfully.", tc_ctr);
        end
      else
        begin
          $display("*** %02d test cases completed.", tc_ctr);
          $display("*** %02d errors detected during testing.", error_ctr);
        end
    end
  endtask // display_test_result


  //----------------------------------------------------------------
  // wait_ready()
  //
  // Wait for the ready flag in the dut to be set.
  // (Actually we wait for either ready or valid to be set.)
  //
  // Note: It is the callers responsibility to call the function
  // when the dut is actively processing and will in fact at some
  // point set the flag.
  //----------------------------------------------------------------
  task wait_ready;
    begin
      read_data = 0;

      while (read_data == 0)
        begin
          read_word(ADDR_STATUS);
        end
    end
  endtask // wait_ready


  //----------------------------------------------------------------
  // write_word()
  //
  // Write the given word to the DUT using the DUT interface.
  //----------------------------------------------------------------
  task write_word(input [7 : 0]  address,
                  input [31 : 0] word);
    begin
      if (DEBUG)
        begin
          $display("*** Writing 0x%08x to 0x%02x.", word, address);
          $display("");
        end

      tb_address = address;
      tb_write_data = word;
      tb_cs = 1;
      tb_we = 1;
      #(CLK_PERIOD);
      tb_cs = 0;
      tb_we = 0;
    end
  endtask // write_word


  //----------------------------------------------------------------
  // write_block()
  //
  // Write the given block to the dut.
  //----------------------------------------------------------------
  task write_block(input [511 : 0] block);
    begin
      write_word(ADDR_BLOCK0,  block[511 : 480]);
      write_word(ADDR_BLOCK1,  block[479 : 448]);
      write_word(ADDR_BLOCK2,  block[447 : 416]);
      write_word(ADDR_BLOCK3,  block[415 : 384]);
      write_word(ADDR_BLOCK4,  block[383 : 352]);
      write_word(ADDR_BLOCK5,  block[351 : 320]);
      write_word(ADDR_BLOCK6,  block[319 : 288]);
      write_word(ADDR_BLOCK7,  block[287 : 256]);
      write_word(ADDR_BLOCK8,  block[255 : 224]);
      write_word(ADDR_BLOCK9,  block[223 : 192]);
      write_word(ADDR_BLOCK10, block[191 : 160]);
      write_word(ADDR_BLOCK11, block[159 : 128]);
      write_word(ADDR_BLOCK12, block[127 :  96]);
      write_word(ADDR_BLOCK13, block[95  :  64]);
      write_word(ADDR_BLOCK14, block[63  :  32]);
      write_word(ADDR_BLOCK15, block[31  :   0]);
    end
  endtask // write_block


  //----------------------------------------------------------------
  // read_word()
  //
  // Read a data word from the given address in the DUT.
  // the word read will be available in the global variable
  // read_data.
  //----------------------------------------------------------------
  task read_word(input [7 : 0]  address);
    begin
      tb_address = address;
      tb_cs = 1;
      tb_we = 0;
      #(CLK_PERIOD);
      read_data = tb_read_data;
      tb_cs = 0;

      if (DEBUG)
        begin
          $display("*** Reading 0x%08x from 0x%02x.", read_data, address);
          $display("");
        end
    end
  endtask // read_word

  //----------------------------------------------------------------
  // read_digest()
  //
  // Read the digest in the dut. The resulting digest will be
  // available in the global variable digest_data.
  //----------------------------------------------------------------
  task read_digest;
    begin
      read_word(ADDR_DIGEST0);
      digest_data[255 : 224] = read_data;
      read_word(ADDR_DIGEST1);
      digest_data[223 : 192] = read_data;
      read_word(ADDR_DIGEST2);
      digest_data[191 : 160] = read_data;
      read_word(ADDR_DIGEST3);
      digest_data[159 : 128] = read_data;
      read_word(ADDR_DIGEST4);
      digest_data[127 :  96] = read_data;
      read_word(ADDR_DIGEST5);
      digest_data[95  :  64] = read_data;
      read_word(ADDR_DIGEST6);
      digest_data[63  :  32] = read_data;
      read_word(ADDR_DIGEST7);
      digest_data[31  :   0] = read_data;
    end
  endtask // read_digest


  //----------------------------------------------------------------
  // single_block_test()
  //
  //
  // Perform test of a single block digest.
  //----------------------------------------------------------------
  task single_block_test(input           mode,
                         input [511 : 0] block,
                         input [255 : 0] expected);
    begin
      $display("*** TC%01d - Single block test started.", tc_ctr);

      write_block(block);

      if (mode)
        write_word(ADDR_CTRL, (CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE + CTRL_INIT_VALUE));
      else
        write_word(ADDR_CTRL, CTRL_INIT_VALUE);

      #(CLK_PERIOD);
      wait_ready();
	  read_word(ADDR_STATUS);
	  write_word(ADDR_IRQ_CLR, IRQ_CLR);
	  #(CLK_PERIOD);
	  write_word(ADDR_CTRL, 0);
	  read_word(ADDR_STATUS);
      read_digest();

      // We need to ignore the LSW in SHA224 mode.
      if (mode == SHA224_MODE)
        digest_data[31 : 0] = 32'h0;

      if (digest_data == expected)
        begin
          $display("TC%01d: OK.", tc_ctr);
        end
      else
        begin
          $display("TC%01d: ERROR.", tc_ctr);
          $display("TC%01d: Expected: 0x%064x", tc_ctr, expected);
          $display("TC%01d: Got:      0x%064x", tc_ctr, digest_data);
          error_ctr = error_ctr + 1;
        end
      $display("*** TC%01d - Single block test done.", tc_ctr);
      tc_ctr = tc_ctr + 1;
    end
  endtask // single_block_test


  //----------------------------------------------------------------
  // double_block_test()
  //
  //
  // Perform test of a double block digest. Note that we check
  // the digests for both the first and final block.
  //----------------------------------------------------------------
  task double_block_test(input           mode,
                         input [511 : 0] block0,
                         input [255 : 0] expected0,
                         input [511 : 0] block1,
                         input [255 : 0] expected1
                        );
    begin
      $display("*** TC%01d - Double block test started.", tc_ctr);

      // First block
      write_block(block0);

      if (mode)
        write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_INIT_VALUE));
      else
        write_word(ADDR_CTRL, CTRL_INIT_VALUE);

      #(CLK_PERIOD);
      wait_ready();
      read_digest();

      // We need to ignore the LSW in SHA224 mode.
      if (mode == SHA224_MODE)
        digest_data[31 : 0] = 32'h0;

      if (digest_data == expected0)
        begin
          $display("TC%01d first block: OK.", tc_ctr);
        end
      else
        begin
          $display("TC%01d: ERROR in first digest", tc_ctr);
          $display("TC%01d: Expected: 0x%064x", tc_ctr, expected0);
          $display("TC%01d: Got:      0x%064x", tc_ctr, digest_data);
          error_ctr = error_ctr + 1;
        end

      // Final block
      write_block(block1);

      if (mode)
        write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      else
        write_word(ADDR_CTRL, CTRL_NEXT_VALUE);

      #(CLK_PERIOD);
      wait_ready();
      read_digest();

      // We need to ignore the LSW in SHA224 mode.
      if (mode == SHA224_MODE)
        digest_data[31 : 0] = 32'h0;

      if (digest_data == expected1)
        begin
          $display("TC%01d final block: OK.", tc_ctr);
        end
      else
        begin
          $display("TC%01d: ERROR in final digest", tc_ctr);
          $display("TC%01d: Expected: 0x%064x", tc_ctr, expected1);
          $display("TC%01d: Got:      0x%064x", tc_ctr, digest_data);
          error_ctr = error_ctr + 1;
        end

      $display("*** TC%01d - Double block test done.", tc_ctr);
      tc_ctr = tc_ctr + 1;
    end
  endtask // double_block_test


  //----------------------------------------------------------------
  // sha256_tests()
  //----------------------------------------------------------------
  task sha256_tests;
    begin : sha256_tests_block
      reg [511 : 0] tc0;
      reg [255 : 0] res0;

      reg [511 : 0] tc1_0;
      reg [255 : 0] res1_0;
      reg [511 : 0] tc1_1;
      reg [255 : 0] res1_1;

      $display("*** Testcases for sha256 functionality started.");
		 // TC1: Single block message: "tanphandev".

      tc0 = 512'h74616e7068616e646576800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000050;
      res0 = 256'h85e9a47fc5dc216f9b3ff562488d35c93210cfd8d265688dfeb0612c56f76886;

      single_block_test(SHA256_MODE, tc0, res0);

      $display("*** Testcases for sha256 functionality completed.");
    end
  endtask // sha256_tests



  //----------------------------------------------------------------
  // issue_test()
  //----------------------------------------------------------------
  task issue_test;
    reg [511 : 0] block0;
    reg [511 : 0] block1;
    reg [511 : 0] block2;
    reg [511 : 0] block3;
    reg [511 : 0] block4;
    reg [511 : 0] block5;
    reg [511 : 0] block6;
    reg [511 : 0] block7;
    reg [511 : 0] block8;
    reg [255 : 0] expected;
    begin : issue_test
      block0 = 512'h6b900001_496e2074_68652061_72656120_6f662049_6f542028_496e7465_726e6574_206f6620_5468696e_6773292c_206d6f72_6520616e_64206d6f_7265626f_6f6d2c20;
      block1 = 512'h69742068_61732062_65656e20_6120756e_69766572_73616c20_636f6e73_656e7375_73207468_61742064_61746120_69732074_69732061_206e6577_20746563_686e6f6c;
      block2 = 512'h6f677920_74686174_20696e74_65677261_74657320_64656365_6e747261_6c697a61_74696f6e_2c496e20_74686520_61726561_206f6620_496f5420_28496e74_65726e65;
      block3 = 512'h74206f66_20546869_6e677329_2c206d6f_72652061_6e64206d_6f726562_6f6f6d2c_20697420_68617320_6265656e_20612075_6e697665_7273616c_20636f6e_73656e73;
      block4 = 512'h75732074_68617420_64617461_20697320_74697320_61206e65_77207465_63686e6f_6c6f6779_20746861_7420696e_74656772_61746573_20646563_656e7472_616c697a;
      block5 = 512'h6174696f_6e2c496e_20746865_20617265_61206f66_20496f54_2028496e_7465726e_6574206f_66205468_696e6773_292c206d_6f726520_616e6420_6d6f7265_626f6f6d;
      block6 = 512'h2c206974_20686173_20626565_6e206120_756e6976_65727361_6c20636f_6e73656e_73757320_74686174_20646174_61206973_20746973_2061206e_65772074_6563686e;
      block7 = 512'h6f6c6f67_79207468_61742069_6e746567_72617465_73206465_63656e74_72616c69_7a617469_6f6e2c49_6e207468_65206172_6561206f_6620496f_54202849_6e746572;
      block8 = 512'h6e657420_6f662054_68696e67_73292c20_6d6f7265_20616e64_206d6f72_65800000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_000010e8;

      expected = 256'h7758a30bbdfc9cd92b284b05e9be9ca3d269d3d149e7e82ab4a9ed5e81fbcf9d;

      $display("Running test for 9 block issue.");
      tc_ctr = tc_ctr + 1;
      write_block(block0);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_INIT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block1);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block2);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block3);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block4);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block5);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block6);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block7);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      write_block(block8);
      write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
      #(CLK_PERIOD);
      wait_ready();

      read_digest();
      if (digest_data == expected)
        begin
          $display("Digest ok.");
        end
      else
        begin
          $display("ERROR in digest");
          $display("Expected: 0x%064x", expected);
          $display("Got:      0x%064x", digest_data);
          error_ctr = error_ctr + 1;
        end
    end
  endtask // issue_test

  
//hash block header 
task hash_block_header(input [639:0] header);
    reg [511 : 0] block1_hash1;
    reg [511 : 0] block2_hash1;
	 reg [511 : 0] block1_hash2;
	 reg [1023:0] padding_block_hash1;
	 reg [511:0] padding_block_hash2;

	
	 begin : hash_block_header
			automatic  integer i;
		// padding for block header
		//copy block header
		  padding_block_hash1[1023:384] = header;
	 
		// add 1 after block header
		  padding_block_hash1[383] = 1'b1;

	    // add bits 0 until remain 64 bits
		  for (i = 382; i > 63; i = i - 1) 
		  begin
			 padding_block_hash1[i] = 1'b0;
		  
		  end
		
		 // add 64bits end is length block header
			padding_block_hash1[63:0] = 64'h00000280;
				
		  // sperate
		  block1_hash1 = padding_block_hash1[1023:512];
		  block2_hash1 = padding_block_hash1[511:0];		
				
			// check result
			/*
			begin
				 $display("header = 0x%0128x", padding_block_hash1);
				 $display("BLOCK1 = 0x%064x", block1_hash1);
				 $display("BLOCK2 = 0x%064x", block2_hash1);
			  end
			  */
		  //hash time 1
		  	tc_ctr = tc_ctr + 1;
			write_block(block1_hash1);
			write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_INIT_VALUE));
			#(CLK_PERIOD);
			wait_ready();

			write_block(block2_hash1);
			write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_NEXT_VALUE));
			#(CLK_PERIOD);
			wait_ready();

			read_digest();
						//show digest hash once
			/*
			  begin
				 $display("HASH once FINISH !");
				 $display("HASH_ONCE: 0x%064x", digest_data);
				 error_ctr = error_ctr + 1;
			
			  end
			*/  
			//HASH twice
			
			//padding
		  	  padding_block_hash2[511:256] = digest_data;
			//add bit 1
			  padding_block_hash2[255] = 1'b1;
			//add bit 0
			  for (i = 254; i > 63; i = i - 1) 
				  begin
						 padding_block_hash2[i] = 1'b0;
					  
					end
			//add 64bit length hash1
				padding_block_hash2[63:0] = 64'h00000100;
				
			//past cho block 1
				block1_hash2= padding_block_hash2[511:0];	
			//checkout padding hash twice
			/*
				begin
				 $display("padding_after_hash_twice = 0x%0128x", padding_block_hash2);
				 $display("BLOCK1_hash_TWICE = 0x%064x", block1_hash2);
				end
			*/
			
			//hash2
				write_block(block1_hash2);
				write_word(ADDR_CTRL, (CTRL_MODE_VALUE + CTRL_INIT_VALUE));
				#(CLK_PERIOD);
				wait_ready();

				read_digest();
				//show hash twice
				/*
				  begin
					 $display("HASH TWICE FINISH!");
					 $display("HASH_TWICE: 0x%064x", digest_data);
					 error_ctr = error_ctr + 1;
				  end
				  */
				
    end

endtask // hash_block_header
  
//reverse byte 
task reverse_byte(input [255:0] digest_data);
	begin:reverse_byte
	reverse_digest[255:248] = digest_data[7:0];
	reverse_digest[247:240] = digest_data[15:8];
	reverse_digest[239:232] = digest_data[23:16];
	reverse_digest[231:224] = digest_data[31:24];
	reverse_digest[223:216] = digest_data[39:32];
	reverse_digest[215:208] = digest_data[47:40];
	reverse_digest[207:200] = digest_data[55:48];
	reverse_digest[199:192] = digest_data[63:56];
	reverse_digest[191:184] = digest_data[71:64];
	reverse_digest[183:176] = digest_data[79:72];
	reverse_digest[175:168] = digest_data[87:80];
	reverse_digest[167:160] = digest_data[95:88];
	reverse_digest[159:152] = digest_data[103:96];
	reverse_digest[151:144] = digest_data[111:104];
	reverse_digest[143:136] = digest_data[119:112];
	reverse_digest[135:128] = digest_data[127:120];
	reverse_digest[127:120] = digest_data[135:128];
	reverse_digest[119:112] = digest_data[143:136];
	reverse_digest[111:104] = digest_data[151:144];
	reverse_digest[103:96] = digest_data[159:152];
	reverse_digest[95:88] = digest_data[167:160];
	reverse_digest[87:80] = digest_data[175:168];
	reverse_digest[79:72] = digest_data[183:176];
	reverse_digest[71:64] = digest_data[191:184];
	reverse_digest[63:56] = digest_data[199:192];
	reverse_digest[55:48] = digest_data[207:200];
	reverse_digest[47:40] = digest_data[215:208];
	reverse_digest[39:32] = digest_data[223:216];
	reverse_digest[31:24] = digest_data[231:224];
	reverse_digest[23:16] = digest_data[239:232];
	reverse_digest[15:8] = digest_data[247:240];
	reverse_digest[7:0] = digest_data[255:248];
	
	end
endtask 
  
//mining
task mining;

	 reg [639:0] header;
    reg [255 : 0] expected;
	 reg [31:0] nounce;
    begin : mining
		automatic integer break_loop = 0;
		header = 640'h00a0112e535d512362f80687511204abed45ae64cca1a05e822a00000000000000000000937413ff6cdb14f48933dbf23ebbe375de119214347d8a368eac954f94a1141e85d82e643e02061700000000;	
		target = 256'h00000000000000000006023e0000000000000000000000000000000000000000;
		expected = 256'h775449978ab7060338495193fd5e30200ec4ea03199d05000000000000000000;
	 	nounce = 32'h9448A7F8;// true nounce = 0x9448a802
		

		while (nounce < 32'hffffffff && !break_loop)
			begin
				header[31:0] = nounce;
				$display("Block_header: 0x%080x", header);
				$display("Nounce: 0x%04x", nounce);
				hash_block_header(header);
				reverse_byte(digest_data);
				if(reverse_digest < target)
				begin
					$display("MINING SUCCESS!");
					$display("Block_header_valid : 0x%080x", header);
					$display("Nounce_valid :0x%04x", nounce);
					$display("Hash_valid : 0x%064x", reverse_digest);
					break_loop = 1;
				end
				nounce = nounce + 1'b1;
				
			end

		end
  endtask // mining


  //----------------------------------------------------------------
  // The main test functionality.
  //----------------------------------------------------------------
  initial
    begin : main
      $display("   -- Testbench for sha256 started --");

      init_sim();
      reset_dut();
	  sha256_tests();
     // mining();
      display_test_result();
      $display("   -- Testbench for sha256 done. --");
      $finish;
    end // main
endmodule // tb_sha256
