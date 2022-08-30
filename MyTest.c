#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fake65c02.h"

uint8 mem[65536];

uint8 read6502(ushort addr) {
	return mem[addr];
}

void write6502(ushort addr, uint8 val) {
	mem[addr] = val;
}

// ***************************************************************************************
int main(int argc, char **argv) {
	mem[0xfffc] = 0;
	mem[0xfffd] = 0x80;
	printf("%x\n", clockticks6502);
	mem[0x8000] = 0xa9;
	mem[0x8001] = 0xff;
	mem[0x8002] = 0x8d;
	mem[0x8003] = 0x02;
	mem[0x8004] = 0x60;
	mem[0x8005] = 0xa9;
	mem[0x8006] = 0x50;
	mem[0x8007] = 0x8d;

	mem[0x8008] = 0x00;
	mem[0x8009] = 0x60;
	mem[0x800a] = 0x6a;
	mem[0x800b] = 0x8d;
	mem[0x800c] = 0x00;
	mem[0x800d] = 0x60;
	mem[0x800e] = 0x4c;
	mem[0x800f] = 0x0a;

	mem[0x8010] = 0x80;
	mem[0x8011] = 0x00;
	mem[0x8012] = 0x00;
	mem[0x8013] = 0x00;

	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	reset6502();
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);

	puts("*****");
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);	
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	printf("%x", step6502());
	printf("%x %x %x %x %x %x\n", pc, sp, a, x, y, status);
	return 0;
}

