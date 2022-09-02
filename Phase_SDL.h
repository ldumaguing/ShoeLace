#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

extern uint8 RAM[];

void make_window(SDL_Window*);
void close_window(SDL_Window*);
void pause_SDL();

// ***************************************************************************************
void Phase_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
		exit(1); }
	
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
		
		
		
		RAM[0x0200] = 0; }  // reset SDL flags

}

// ***************************************************************************************
void pause_SDL() {
	puts("pausing");
	SDL_Delay(5000);
}

// ***************************************************************************************
void make_window(SDL_Window* win) {
	puts("open window");

	win = SDL_CreateWindow("Hello, CS50!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									640, 480, 0);

	if (!win) {
		printf("error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1); }}

// ***************************************************************************************
void close_window(SDL_Window* win) {
	puts("close window");
	SDL_DestroyWindow(win);
	SDL_Quit(); }






