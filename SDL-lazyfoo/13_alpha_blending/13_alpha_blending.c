#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();
bool loadMedia();
void closeSDL();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

typedef struct {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

	bool ( *loadFromFile )( void*, char* );
	void ( *free )( void* );
	void ( *setColor )( void*, Uint8, Uint8, Uint8 );
	void ( *setBlendMode )( void*, SDL_BlendMode );
	void ( *setAlpha )( void*, Uint8 );
	void ( *render )( void*, int , int , SDL_Rect* );
	int ( *getWidth )( void* );
	int ( *getHeight )( void* ); } LTexture;

bool LTexture__loadFromFile( void* self, char* path ) {
	((LTexture *)self)->free(self);

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

void LTexture__free(void* self) {
	if( ((LTexture *)self)->mTexture != NULL ) {
		SDL_DestroyTexture( ((LTexture *)self)->mTexture );
		((LTexture *)self)->mTexture = NULL;
		((LTexture *)self)->mWidth = 0;
		((LTexture *)self)->mHeight = 0; }}

void LTexture__setColor( void* self, Uint8 red, Uint8 green, Uint8 blue ) {
	SDL_SetTextureColorMod( ((LTexture *)self)->mTexture, red, green, blue ); }

void LTexture__setBlendMode( void* self, SDL_BlendMode blending ) {
	SDL_SetTextureBlendMode( ((LTexture *)self)->mTexture, blending ); }
		
void LTexture__setAlpha( void* self, Uint8 alpha ) {
	SDL_SetTextureAlphaMod( ((LTexture *)self)->mTexture, alpha ); }

void LTexture__render( void* self, int x, int y, SDL_Rect* clip ) {
	SDL_Rect renderQuad = { x, y, ((LTexture *)self)->mWidth, ((LTexture *)self)->mHeight };

	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h; }

	SDL_RenderCopy( gRenderer, ((LTexture *)self)->mTexture, clip, &renderQuad ); }

int LTexture__getWidth( void* self ) {
	return ((LTexture *)self)->mWidth; }

int LTexture__getHeight( void* self ) {
	return ((LTexture *)self)->mHeight; }

void glue_LTexture(LTexture* X) {
	X->loadFromFile = &LTexture__loadFromFile;
	X->free = &LTexture__free;
	X->setColor = &LTexture__setColor;
	X->setBlendMode = &LTexture__setBlendMode;
	X->setAlpha = &LTexture__setAlpha;
	X->render = &LTexture__render;
	X->getWidth = &LTexture__getWidth;
	X->getHeight = &LTexture__getHeight; }

// ***************************************************************************************
LTexture gModulatedTexture;
LTexture gBackgroundTexture;

bool init() {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false; }

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" ); }

	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false; }

	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false; }

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false; }

	return true; }

bool loadMedia() {
	if( !gModulatedTexture.loadFromFile( &gModulatedTexture, "fadeout.png" ) ) {
		printf( "Failed to load front texture!\n" );
		return false; }

	gModulatedTexture.setBlendMode( &gModulatedTexture, SDL_BLENDMODE_BLEND );

	if( !gBackgroundTexture.loadFromFile( &gBackgroundTexture, "fadein.png" ) ) {
		printf( "Failed to load background texture!\n" );
		return false; }
	
	return true; }

void closeSDL() {
	gModulatedTexture.free( &gModulatedTexture );
	gBackgroundTexture.free( &gBackgroundTexture );

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit(); }

// ***************************************************************************************
int main( int argc, char* args[] ) {
	glue_LTexture( &gModulatedTexture );
	glue_LTexture( &gBackgroundTexture );

	if( !init() ) {
		printf( "Failed to initialize!\n" );
		return 1; }

	if( !loadMedia() ) {
		printf( "Failed to load media!\n" );
		return 1; }

	bool quit = false;
	SDL_Event e;
	Uint8 a = 255;
	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true; }
			else if( e.type == SDL_KEYDOWN ) {
				if( e.key.keysym.sym == SDLK_w ) {
					if( a + 32 > 255 ) {
						a = 255; }
					else {
						a += 32; }}
				else if( e.key.keysym.sym == SDLK_s ) {
					if( a - 32 < 0 ) {
						a = 0; }
					else {
						a -= 32; }}}}

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		gBackgroundTexture.render( &gBackgroundTexture, 0, 0, NULL );

		gModulatedTexture.setAlpha( &gModulatedTexture, a );
		gModulatedTexture.render( &gModulatedTexture, 0, 0, NULL );

		SDL_RenderPresent( gRenderer ); }

	closeSDL();

	return 0; }



