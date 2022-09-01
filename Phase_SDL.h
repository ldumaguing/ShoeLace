extern uint8 RAM[];

void Phase_SDL() {
	printf("%x\n", RAM[0x0200]);
	if (RAM[0x0200] == 1) {
		puts("------------ ok");
		RAM[0x0200] = 0; }

}
