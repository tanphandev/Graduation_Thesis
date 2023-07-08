#include "SHA.h"

void write_word(int *btr, int addr, int value) {
	*(btr + addr) = value;
}

unsigned int read_word(int *btr, int addr) {
	return *(btr + addr);
}

void write_ctrl(int SHA_BASE, int value) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	write_word(btr, ADDR_CTRL, value);
}

void write_block(int SHA_BASE, int MEM_BASE) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	alt_u32 *mem = (alt_32*) MEM_BASE;
	char index;
	for (index = 0; index < 16; index++) {
		write_word(btr, ADDR_BLOCK_START + index, *(mem + index));
	}
}

void write_clr_irq(int SHA_BASE) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	write_word(btr, ADDR_IRQ_CLR, IRQ_CLR);
}

unsigned int read_control(int SHA_BASE) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	return read_word(btr, ADDR_CTRL);
}

unsigned int read_status(int SHA_BASE) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	return read_word(btr, ADDR_STATUS);
}

unsigned int read_block(int SHA_BASE, char index) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	return read_word(btr, ADDR_BLOCK_START + index);
}

void read_digest(int SHA_BASE, int MEM_BASE) {
	alt_u32 *btr = (alt_32*) SHA_BASE;
	alt_u32 *mem = (alt_32*) MEM_BASE;
	char index = 0;
	for (index = 0; index < 8; index++) {
		*(mem+ index) = read_word(btr, ADDR_DIGEST_START + index);
	}
}

int getLength(char Message[]) {
	int length;
	length = 0;
	while (1) {
		if (Message[length] != '\n')
			length++;
		else
			break;
	}
	return length;
}

int Padding(unsigned int Block[], char Message[], int l) {
	int i, j, count, NumberBlock;
	unsigned int temp;

	j = 0;
	count = 0;
	temp = 0;
	Block[j] = 0;

	for (i = 0; i < l; i++) {
		temp = Message[i];
		if (count < 3) {
			temp = temp << (3 - count) * 8;
		}
		Block[j] = Block[j] | temp;
		count++;
		if (count == 4) {
			j++;
			Block[j] = 0;
			temp = 0;
			count = 0;
		}
	}
	if ((l % 4) == 0) {
		Block[l / 4] = 0x80 << 24;
	} else {
		j = l / 4;
		i = l % 4;
		if (i < 4) {
			temp = 0x80 << (3 - i) * 8;
		} else {
			temp = 0x80;
		}
		Block[j] = Block[j] | temp;

	}

	if (l <= 55) {
		for (i = j + 1; i < 15; i++) {
			Block[i] = 0;
			NumberBlock = 1;
		}
	}

	Block[i] = l * 8;
	for (i = i + 1; i < 64; i++) {
		Block[i] = 0;
	}
	return NumberBlock;
}

void storeTargetIntoMemory(int MEM_BASE, unsigned int Target[], int length) {
		int i , j, count,l;
		l = length;
		unsigned int temp;

		j = 0;
		count = 0;
		temp = 0;
		alt_32 *mem = (alt_32*)MEM_BASE;
		*(mem + j) = 0;

		for (i = 0; i < l; i++) {
			temp = Target[i];
			if (count < 3) {
				temp = temp << (3-count)*8;
			}
			*(mem + j)= *(mem + j) | temp;
			count++;
			if (count == 4) {
				j++;
				*(mem + j) = 0;
				temp = 0;
				count = 0;
			}
		}
}

int Padding_Mem(int MEM_BASE, unsigned int Message[], int length) {
		int i , j, count, NumberBlock,l;
		l = length;
		unsigned int temp;

		j = 0;
		count = 0;
		temp = 0;
		alt_32 *mem = (alt_32*)MEM_BASE;
		*(mem + j) = 0;

		for (i = 0; i < l; i++) {
			temp = Message[i];
			if (count < 3) {
				temp = temp << (3-count)*8;
			}
			*(mem + j)= *(mem + j) | temp;
			count++;
			if (count == 4) {
				j++;
				*(mem + j) = 0;
				temp = 0;
				count = 0;
			}
		}
		if ((l % 4) == 0) {
			*(mem + l/4) = 0x80 << 24;
		}
		else {
			j = l / 4;
			i = l % 4;
			if (i < 4) {
				temp = 0x80 << (3 - i) * 8;
			}
			else {
				temp = 0x80;
			}
			*(mem + j) = *(mem + j) | temp;

		}

		if (l <= 55) {
			for (i = j + 1; i < 15; i++) {
				*(mem + i) = 0;
				NumberBlock = 1;
			}
		}
		else if (l >= 56 && l <= 119) {
			for (i = j + 1; i < 31; i++) {
				*(mem + i) = 0;
				NumberBlock = 2;
			}
		}
		else if (l >= 120 && l <= 183) {
			for (i = j + 1; i < 47; i++) {
				*(mem + i) = 0;
				NumberBlock = 3;
			}
		}
		*(mem + i) = l * 8;
		for (i = i + 1; i < 64; i++) {
			*(mem + i) = 0;
		}
		return NumberBlock;
    }

unsigned int SHA_Init(int SHA_BASE, int MEM_BASE, int ctrl_value) {
	write_ctrl(SHA_BASE, 0x0); // clear control
	write_clr_irq(SHA_BASE); //clear interrupt
	write_block(SHA_BASE, MEM_BASE);
	write_ctrl(SHA_BASE, ctrl_value);
	return read_control(SHA_BASE);
}

void reverse_byte_in_memory(int MEM_BASE, unsigned int length_word) {
    unsigned int *memory_ptr = (unsigned int*)MEM_BASE;

    for (unsigned int i = 0; i < length_word; i++) {
        unsigned int word = *(memory_ptr + i);
        unsigned int reversed_word = ((word & 0x000000FF) << 24) |
                                    ((word & 0x0000FF00) << 8) |
                                    ((word & 0x00FF0000) >> 8) |
                                    ((word & 0xFF000000) >> 24);
        *(memory_ptr + i)= reversed_word;
    }
}

unsigned int compareWithTarget(int MEM_BASE_DIGEST, int MEM_BASE_TARGET, unsigned int length_word) {
	alt_u32 *memory_base_digest = (alt_32*) MEM_BASE_DIGEST;
	alt_u32 *memory_base_target = (alt_32*) MEM_BASE_TARGET;
	unsigned int index =0;
    for (index = 0; index < length_word; index++) {
        if (*(memory_base_digest + (7 - index)) < *(memory_base_target + index )) {
        	return 1;
        }
        else if (*(memory_base_digest + (7 - index)) > *(memory_base_target + index )) {
        	return 0;
        }
    }
    return 0;
}

void padding_for_first_hash(int MEM_BASE){
	alt_u32 *memory_ptr = (alt_32*) MEM_BASE;
	*(memory_ptr + 8) = 0x80000000;
	*(memory_ptr + 9) = 0x0;
	*(memory_ptr + 10) = 0x0;
	*(memory_ptr + 11) = 0x0;
	*(memory_ptr + 12) = 0x0;
	*(memory_ptr + 13) = 0x0;
	*(memory_ptr + 14) = 0x0;
	*(memory_ptr + 15) = 0x00000100;
}
