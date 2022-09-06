#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();
bool loadMedia();
void closeSDL();

SDL_Surface* loadSurface( char* );

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStretchedSurface = NULL;

bool init() {
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false; }
	else {
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false; }
		else {
			gScreenSurface = SDL_GetWindowSurface( gWindow ); }}

	return success; }

bool loadMedia() {
	bool success = true;

	gStretchedSurface = loadSurface( "stretch.bmp" );
	if( gStretchedSurface == NULL ) {
		printf( "Failed to load stretching image!\n" );
		success = false; }

	return success; }

void closeSDL() {
	SDL_FreeSurface( gStretchedSurface );
	gStretchedSurface = NULL;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	SDL_Quit(); }

SDL_Surface* loadSurface( char* path ) {
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = SDL_LoadBMP( path );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() ); }
	else {
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() ); }

		SDL_FreeSurface( loadedSurface ); }

	return optimizedSurface; }

int main( int argc, char* args[] ) {
	if( !init() ) {
		printf( "Failed to initialize!\n" ); }
	else {
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" ); }
		else {
			bool quit = false;

			SDL_Event e;

			while( !quit ) {
				while( SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT ) {
						quit = true; }}

				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );

				SDL_UpdateWindowSurface( gWindow ); }}}

	closeSDL();

	return 0; }







