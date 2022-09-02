#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

extern uint8 RAM[];

void make_window(SDL_Window*);
void close_window(SDL_Window*);
void pause_SDL();

// ***************************************************************************************
void Phase_SDL() {
	SDL_Window* win;

	
	if (RAM[0x0200] == 1) {
		switch(RAM[0x0201]) {
			case 1:
				make_window(win);
				break;
			case 2:
				close_window(win);
				break;
			case 3:
				pause_SDL();
				break;
			default:
				puts("--------- ok");
			}
		
		
		
		RAM[0x0200] = 0; }

}

// ***************************************************************************************
void pause_SDL() {
	puts("pausing");
	SDL_Delay(5000);
}

// ***************************************************************************************
void make_window(SDL_Window* win) {
	puts("open window");
}

// ***************************************************************************************
void close_window(SDL_Window* win) {
	puts("close window");
}
