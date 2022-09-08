#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init();
bool loadMedia();
void closeSDL();

typedef struct {  // LTexture
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

	bool ( *loadFromFile )( void*, char* );
	void ( *freeSDL )( void* );
	void ( *renderSDL )( void*, int x, int y );
	int ( *getWidth )( void* );
	int ( *getHeight )( void* ); } LTexture;

int getWidth( void* self ) {
	return ((LTexture *)self)->mWidth; }

int getHeight( void* self ) {
	return ((LTexture *)self)->mHeight; }

void freeSDL( void* self) {
	if( ((LTexture *)self)->mTexture != NULL ) {
		SDL_DestroyTexture( ((LTexture *)self)->mTexture );
		((LTexture *)self)->mTexture = NULL;
		((LTexture *)self)->mWidth = 0;
		((LTexture *)self)->mHeight = 0; }}

bool loadFromFile( void* self, char* path ) {
	((LTexture *)self)->freeSDL( self );

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() ); }
	else {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() ); }
		else {
			((LTexture *)self)->mWidth = loadedSurface->w;
			((LTexture *)self)->mHeight = loadedSurface->h; }

		SDL_FreeSurface( loadedSurface ); }

	((LTexture *)self)->mTexture = newTexture;
	return ((LTexture *)self)->mTexture != NULL; }

void renderSDL( void* self, int x, int y ) {
	SDL_Rect renderQuad = { x, y, ((LTexture *)self)->mWidth, ((LTexture *)self)->mHeight };
	SDL_RenderCopy( gRenderer, ((LTexture *)self)->mTexture, NULL, &renderQuad ); }

LTexture gFooTexture;
LTexture gBackgroundTexture;

void glue_LTexture(LTexture* X) {
	X->loadFromFile = &loadFromFile;
	X->freeSDL = &freeSDL;
	X->renderSDL = &renderSDL;
	X->getWidth = &getWidth;
	X->getHeight = &getHeight; }

// ***************************************************************************************
bool init() {
	bool success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false; }
	else {
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" ); }

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false; }
		else {
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false; }
			else {
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; }}}}

	return success; }

bool loadMedia() {
	bool success = true;

	if( !gFooTexture.loadFromFile( &gFooTexture, "foo.png" ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false; }

	if( !gBackgroundTexture.loadFromFile( &gBackgroundTexture, "background.png" ) ) {
		printf( "Failed to load background texture image!\n" );
		success = false; }

	return success; }

void closeSDL() {
	gFooTexture.freeSDL(&gFooTexture);
	gBackgroundTexture.freeSDL(&gBackgroundTexture);

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit(); }

// ***************************************************************************************
int main( int argc, char* args[] ) {
	glue_LTexture(&gFooTexture);
	glue_LTexture(&gBackgroundTexture);
	
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

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gBackgroundTexture.renderSDL( &gBackgroundTexture, 0, 0 );

				gFooTexture.renderSDL( &gFooTexture, 240, 190 );

				SDL_RenderPresent( gRenderer ); }}}

	closeSDL();

	return 0; }



