#include "sys/alt_stdio.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "SHA.h"

volatile alt_u32 *memory_ptr = (alt_u32*) ONCHIP_MEMORY2_1_BASE;
volatile alt_u32 *mem_base1 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4);
volatile alt_u32 *mem_base2 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4);
volatile alt_u32 *mem_base3 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4);
volatile alt_u32 *mem_base4 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4);
volatile alt_u32 *mem_base5 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4);
volatile alt_u32 *mem_base6 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4);
volatile alt_u32 *mem_base7 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4);
volatile alt_u32 *mem_base8 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4);
volatile alt_u32 *mem_base9 = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4);
volatile alt_u32 *mem_base_target = (alt_u32*)(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4);

volatile alt_u32 index = 0;
unsigned int i = 0;
unsigned int nounce0 = 0x00000000;
unsigned int nounce1 = 0x19999999;
unsigned int nounce2 = 0x33333333;//858.993.459
unsigned int nounce3 = 0x4ccccccc; // 1.288.490.188
unsigned int nounce4 = 0x66666666; // 1.717.986.918
unsigned int nounce5 = 0x7fffffff; //2.147.483.647
unsigned int nounce6 = 0x93333333; //2.469.606.195
unsigned int nounce7 = 0xb3333333; //3.006.477.107 // 3012316214
unsigned int nounce8 = 0xcccccccc; //3.435.973.836
unsigned int nounce9 = 0xe6666666; //3.865.470.566
unsigned int count0 = 0x0;
unsigned int count1 = 0x0;
unsigned int count2 = 0x0;
unsigned int count3 = 0x0;
unsigned int count4 = 0x0;
unsigned int count5 = 0x0;
unsigned int count6 = 0x0;
unsigned int count7 = 0x0;
unsigned int count8 = 0x0;
unsigned int count9 = 0x0;
unsigned int flag0 = 0x0;
unsigned int flag1 = 0x0;
unsigned int flag2 = 0x0;
unsigned int flag3 = 0x0;
unsigned int flag4 = 0x0;
unsigned int flag5 = 0x0;
unsigned int flag6 = 0x0;
unsigned int flag7 = 0x0;
unsigned int flag8 = 0x0;
unsigned int flag9 = 0x0;
unsigned int target[32] = { 0x00 };
unsigned int NumberOfBlock;
unsigned int* final_digest_0;
unsigned int* final_digest_1;
unsigned int* final_digest_2;
unsigned int* final_digest_3;
unsigned int* final_digest_4;
unsigned int* final_digest_5;
unsigned int* final_digest_6;
unsigned int* final_digest_7;
unsigned int* final_digest_8;
unsigned int* final_digest_9;
void SHA_0_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_0_BASE);
	count0++;
	if(count0 == 0x1){
		//init SHA second
		SHA_Init(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE + SHA_BLOCK_SIZE * 4 ,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count0 == 0x2){
		read_digest(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE *4 );
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE *4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE *4 ,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count0 == 0x3){
		flag0 = flag0 | 0x1;
		count0 = 0x0;
	}
}
void SHA_1_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_1_BASE);
	count1++;

	if(count1 == 0x1){
		//init SHA second
		SHA_Init(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count1 == 0x2){
		read_digest(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count1 == 0x3){
		flag1 = flag1 | 0x1;
		count1 = 0x0;
	}
}

void SHA_2_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_2_BASE);
	count2++;

	if(count2 == 0x1){
		//init SHA second
		SHA_Init(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count2 == 0x2){
		read_digest(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count2 == 0x3){
		flag2 = flag2 | 0x1;
		count2 = 0x0;
	}
}

void SHA_3_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_3_BASE);
	count3++;

	if(count3 == 0x1){
		//init SHA second
		SHA_Init(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count3 == 0x2){
		read_digest(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count3 == 0x3){
		flag3 = flag3 | 0x1;
		count3 = 0x0;
	}
}

void SHA_4_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_4_BASE);
	count4++;

	if(count4 == 0x1){
		//init SHA second
		SHA_Init(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count4 == 0x2){
		read_digest(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count4 == 0x3){
		flag4 = flag4 | 0x1;
		count4 = 0x0;
	}
}

void SHA_5_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_5_BASE);
	count5++;

	if(count5 == 0x1){
		//init SHA second
		SHA_Init(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count5 == 0x2){
		read_digest(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count5 == 0x3){
		flag5 = flag5 | 0x1;
		count5 = 0x0;
	}
}

void SHA_6_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_6_BASE);
	count6++;

	if(count6 == 0x1){
		//init SHA second
		SHA_Init(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count6 == 0x2){
		read_digest(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count6 == 0x3){
		flag6 = flag6 | 0x1;
		count6 = 0x0;
	}
}

void SHA_7_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_7_BASE);
	count7++;

	if(count7 == 0x1){
		//init SHA second
		SHA_Init(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count7 == 0x2){
		read_digest(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count7 == 0x3){
		flag7 = flag7 | 0x1;
		count7 = 0x0;
	}
}

void SHA_8_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_8_BASE);
	count8++;

	if(count8 == 0x1){
		//init SHA second
		SHA_Init(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count8 == 0x2){
		read_digest(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count8 == 0x3){
		flag8= flag8 | 0x1;
		count8 = 0x0;
	}
}

void SHA_9_IRQ_Handler(void* isr_context) {
	//clear interrupt
	write_clr_irq(SHA_9_BASE);
	count9++;

	if(count9 == 0x1){
		//init SHA second
		SHA_Init(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + SHA_BLOCK_SIZE * 4,
			CTRL_NEXT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
	}else if(count9 == 0x2){
		read_digest(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4);
		/*-------padding for first hash--------*/
		padding_for_first_hash(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4);
		/*--------Start second hash--------*/
		/*--------init SHA core--------*/
		SHA_Init(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4,
		CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

	}else if(count9 == 0x3){
		flag9= flag9 | 0x1;
		count9 = 0x0;
	}
}

void init_block_header(unsigned int block_header[], int MEM_BASE){
	int NumberOfBlock = 0x0;
	/*--------padding--------*/
	NumberOfBlock = Padding_Mem(MEM_BASE, block_header, 0x50);
}

int main() {
	unsigned int block_header[80] = {0x00, 0xa0, 0x11, 0x2e, 0x53, 0x5d, 0x51, 0x23, 0x62, 0xf8, 0x06, 0x87, 0x51, 0x12, 0x04, 0xab, 0xed, 0x45, 0xae, 0x64, 0xcc, 0xa1, 0xa0, 0x5e, 0x82, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x74, 0x13, 0xff, 0x6c, 0xdb, 0x14, 0xf4, 0x89, 0x33, 0xdb, 0xf2, 0x3e, 0xbb, 0xe3, 0x75, 0xde, 0x11, 0x92, 0x14, 0x34, 0x7d, 0x8a, 0x36, 0x8e, 0xac, 0x95, 0x4f, 0x94, 0xa1, 0x14, 0x1e, 0x85, 0xd8, 0x2e, 0x64, 0x3e, 0x02, 0x06, 0x17, 0x94, 0x48, 0xa8, 0x02};
	int length = 0x0;
	unsigned int exponent = block_header[75];
	unsigned int mantissa[3];
	unsigned int shiftNum = exponent - 3;
	unsigned int limited = 0x1;
	unsigned int limitedLoop = 0xa;
	alt_putstr("Hello from Nios II!\n");

	/*--------register irq with handeler--------*/
	alt_ic_isr_register(SHA_0_IRQ_INTERRUPT_CONTROLLER_ID, SHA_0_IRQ,
			SHA_0_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_1_IRQ_INTERRUPT_CONTROLLER_ID, SHA_1_IRQ,
			SHA_1_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_2_IRQ_INTERRUPT_CONTROLLER_ID, SHA_2_IRQ,
			SHA_2_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_3_IRQ_INTERRUPT_CONTROLLER_ID, SHA_3_IRQ,
			SHA_3_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_4_IRQ_INTERRUPT_CONTROLLER_ID, SHA_4_IRQ,
			SHA_4_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_5_IRQ_INTERRUPT_CONTROLLER_ID, SHA_5_IRQ,
			SHA_5_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_6_IRQ_INTERRUPT_CONTROLLER_ID, SHA_6_IRQ,
			SHA_6_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_7_IRQ_INTERRUPT_CONTROLLER_ID, SHA_7_IRQ,
			SHA_7_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_8_IRQ_INTERRUPT_CONTROLLER_ID, SHA_8_IRQ,
			SHA_8_IRQ_Handler, (void*) 0, (void*) 0);
	alt_ic_isr_register(SHA_9_IRQ_INTERRUPT_CONTROLLER_ID, SHA_9_IRQ,
			SHA_9_IRQ_Handler, (void*) 0, (void*) 0);
	//calculate target
		for (int i = 0; i < 3; i++) {
			mantissa[i] = block_header[74 - i];
		}
		for (int i = 0; i < 3; i++) {
			target[32 - shiftNum - 1 - i ] = mantissa[2 - i];
		}
	//store target into Memory
		storeTargetIntoMemory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, target,32);

	// init block header for core 0
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce0 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE);

	//init block header for core 1
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce1 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4);

	//init block header for core 2
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce2 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4);

	//init block header for core 3
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce3 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4);

	//init block header for core 4
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce4 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4);

	//init block header for core 5
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce5 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4);

	//init block header for core 6
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce6 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4);

	//init block header for core 7
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce7 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4);

	//init block header for core 8
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce8 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4);

	//init block header for core 9
		for(index = 76; index < 80 ; index++){
			block_header[index] = nounce9 >> ((3 - index - 76) * 8) & 0xFF;
		}
		init_block_header(block_header, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4);


		//	init Core 0
		SHA_Init(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1


		//	init Core 1
		SHA_Init(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 2
		SHA_Init(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 3
		SHA_Init(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 4
		SHA_Init(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 5
		SHA_Init(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 6
		SHA_Init(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 7
		SHA_Init(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 8
		SHA_Init(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1

		//	init Core 9
		SHA_Init(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
		printf("Start Mining...\n");
		while(1){
		if ((flag0 & 0x1) == 1) {
			read_digest(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
						printf("\nCORE: SHA_0\n ");
						printf("\nSUCCESS\nDigest Valid\n");
						printf("Nounce = %x \n",nounce0);
						printf("Final Hash: 0x");
						for (unsigned int index = 0; index < 0x8; index++) {
							printf("%.8x",*(memory_ptr + 32 + (7 - index)));
						}
						break;
			}else {
//						printf("\nCORE: SHA_0\n ");
//						printf("Nounce = %x \n", nounce0);
//						printf("Digest invalid!!!\n\n");
						nounce0++;
						*(memory_ptr + 19) = nounce0;
						SHA_Init(SHA_0_BASE, ONCHIP_MEMORY2_1_BASE,
								CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag0 = 0x0;
		}
		if ((flag1 & 0x1) == 1) {
			read_digest(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_1\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce1);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base1 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_1\n ");
//				printf("Nounce = %x \n",nounce1);
//				printf("Digest invalid!!!\n\n");
				nounce1++;
				*(mem_base1 + 19) = nounce1;
				SHA_Init(SHA_1_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag1 = 0x0;
		}
		if ((flag2 & 0x1) == 1) {
			read_digest(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_2\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce2);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base2 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_2\n ");
//				printf("Nounce = %x \n",nounce2);
//				printf("Digest invalid!!!\n\n");
				nounce2++;
				*(mem_base2 + 19) = nounce2;
				SHA_Init(SHA_2_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 2 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag2 = 0x0;
		}
		if ((flag3 & 0x1) == 1) {
			read_digest(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_3\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce3);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base3 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_3\n ");
//				printf("Nounce = %x \n",nounce3);
//				printf("Digest invalid!!!\n\n");
				nounce3++;
				*(mem_base3 + 19) = nounce3;
				SHA_Init(SHA_3_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 3 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag3 = 0x0;
		}
		if ((flag4 & 0x1) == 1) {
			read_digest(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_4\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce4);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base4 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_4\n ");
//				printf("Nounce = %x \n",nounce4);
//				printf("Digest invalid!!!\n\n");
				nounce4++;
				*(mem_base4 + 19) = nounce4;
				SHA_Init(SHA_4_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 4 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag4 = 0x0;
		}
		if ((flag5 & 0x1) == 1) {
			read_digest(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_5\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce5);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base5 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_5\n ");
//				printf("Nounce = %x \n",nounce5);
//				printf("Digest invalid!!!\n\n");
				nounce5++;
				*(mem_base5 + 19) = nounce5;
				SHA_Init(SHA_5_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 5 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag5 = 0x0;
		}
		if ((flag6 & 0x1) == 1) {
			read_digest(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_6\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce6);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base6 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_6\n ");
//				printf("Nounce = %x \n",nounce6);
//				printf("Digest invalid!!!\n\n");
				nounce6++;
				*(mem_base6 + 19) = nounce6;
				SHA_Init(SHA_6_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 6 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag6 = 0x0;
		}
		if ((flag7 & 0x1) == 1) {
			read_digest(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_7\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce7);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base7 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_7\n ");
//				printf("Nounce = %x \n",nounce7);
//				printf("Digest invalid!!!\n\n");
				nounce7++;
				*(mem_base7 + 19) = nounce7;
				SHA_Init(SHA_7_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 7 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag7 = 0x0;
		}
		if ((flag8 & 0x1) == 1) {
			read_digest(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_8\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce8);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base8 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_8\n ");
//				printf("Nounce = %x \n",nounce8);
//				printf("Digest invalid!!!\n\n");
				nounce8++;
				*(mem_base8 + 19) = nounce8;
				SHA_Init(SHA_8_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 8 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag8 = 0x0;
		}
		if ((flag9 & 0x1) == 1) {
			read_digest(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4);
			//reverse_byte
			reverse_byte_in_memory(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4, 0x8);
			if(compareWithTarget(ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4 + BLOCK_HEADER_SIZE * 4, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 12 * 4, 0x8)){
				printf("\nCORE: SHA_9\n ");
				printf("\nSUCCESS\nDigest Valid\n ");
				printf("Nounce = %x \n",nounce9);
				printf("Final Hash: 0x");
				for (unsigned int index = 0; index < 0x8; index++) {
					printf("%.8x",*(mem_base9 + 32 + (7 - index)));
				}
				break;
			}else {
//						printf("\nCORE: SHA_9\n ");
//				printf("Nounce = %x \n",nounce9);
//				printf("Digest invalid!!!\n\n");
				nounce9++;
				*(mem_base9 + 19) = nounce9;
				SHA_Init(SHA_9_BASE, ONCHIP_MEMORY2_1_BASE + STORAGE_SIZE * 9 * 4,
				CTRL_INIT_VALUE + CTRL_IRQ_EN_VALUE + CTRL_MODE_VALUE); //mode = 1, init = 1, irq_en = 1
			}
			flag9 = 0x0;
		}
	}
	return 0;
}
