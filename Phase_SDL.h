extern uint8 RAM[];

void Phase_SDL() {
	printf("%x\n", RAM[0x0200]);
	if (RAM[0x0200] == 1) {
		switch(RAM[0x0201]) {
			case 1:
				make_window();
				break;
			default:
				puts("--------- ok");
			}
		
		
		
		RAM[0x0200] = 0; }

}

void make_window() {
	puts("window");
}

