#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fake65c02.h"
#include "Phase_CPU.h"
#include "Phase_SDL.h"
#include "common.h"

#define ROM_size (0x10000 - 0xC000)

uint8 read6502(ushort addr) {
	return RAM[addr];
}

void write6502(ushort addr, uint8 val) {
	RAM[addr] = val;
}

void loadROM() {

	printf("Loading ROM...\n");
	FILE* fp;
	fp = fopen("rom.bin", "rb");
	fread(ROM, ROM_size, 1, fp);
	fclose(fp);
}

// ***************************************************************************************
int main(int argc, char **argv) {
	RAM[0xfffc] = 0x00;
	RAM[0xfffd] = 0xC0;
	RAM[0x0200] = 0; // SDL flag. 0: do nothing. 1: do command
	RAM[0x0201] = 0; // command 1a
	RAM[0x0202] = 0; // command 1b

	loadROM();
	reset6502();
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);

	for (int i=0; i<50; ++i) {
		Phase_CPU();
		Phase_SDL(); }

	return 0;
}

