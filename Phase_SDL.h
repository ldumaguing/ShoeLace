extern uint8 RAM[];

void make_window();
void close_window();

// ***************************************************************************************
void Phase_SDL() {
	printf("%x\n", RAM[0x0200]);
	if (RAM[0x0200] == 1) {
		switch(RAM[0x0201]) {
			case 1:
				make_window();
				break;
			case 2:
				close_window();
				break;
			default:
				puts("--------- ok");
			}
		
		
		
		RAM[0x0200] = 0; }

}

// ***************************************************************************************
void make_window() {
	puts("open window");
}

// ***************************************************************************************
void close_window() {
	puts("close window");
}
