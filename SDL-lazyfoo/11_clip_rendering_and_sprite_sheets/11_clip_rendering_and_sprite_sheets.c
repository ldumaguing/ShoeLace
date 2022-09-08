#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gSpriteClips[ 4 ];

bool init();
bool loadMedia();
void closeSDL();

// ***************************************************************************************
typedef struct {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	
	bool ( *loadFromFile )( void*, char* );
	void ( *freeSDL )( void* );
	void ( *renderSDL )( void*, int, int, SDL_Rect* );
	int ( *getWidth )( void* );
	int ( *getHeight )( void* ); } LTexture;

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

void freeSDL(void* self) {
	if( ((LTexture *)self)->mTexture != NULL ) {
		SDL_DestroyTexture( ((LTexture *)self)->mTexture );
		((LTexture *)self)->mTexture = NULL;
		((LTexture *)self)->mWidth = 0;
		((LTexture *)self)->mHeight = 0; }}

void renderSDL( void* self, int x, int y, SDL_Rect* clip ) {
	SDL_Rect renderQuad = { x, y, ((LTexture *)self)->mWidth, ((LTexture *)self)->mHeight };

	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h; }

	SDL_RenderCopy( gRenderer, ((LTexture *)self)->mTexture, clip, &renderQuad ); }

int getWidth(void* self) {
	return ((LTexture *)self)->mWidth; }

int getHeight(void* self) {
	return ((LTexture *)self)->mHeight; }

void glue_LTexture(LTexture* X) {
	X->loadFromFile = &loadFromFile;
	X->freeSDL = &freeSDL;
	X->renderSDL = &renderSDL;
	X->getWidth = &getWidth;
	X->getHeight = &getHeight;
}

// ***************************************************************************************
LTexture gSpriteSheetTexture;

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

	if( !gSpriteSheetTexture.loadFromFile( &gSpriteSheetTexture, "dots.png" ) ) {
		printf( "Failed to load sprite sheet texture!\n" );
		success = false; }
	else {
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w = 100;
		gSpriteClips[ 0 ].h = 100;

		gSpriteClips[ 1 ].x = 100;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w = 100;
		gSpriteClips[ 1 ].h = 100;
		
		gSpriteClips[ 2 ].x =   0;
		gSpriteClips[ 2 ].y = 100;
		gSpriteClips[ 2 ].w = 100;
		gSpriteClips[ 2 ].h = 100;

		gSpriteClips[ 3 ].x = 100;
		gSpriteClips[ 3 ].y = 100;
		gSpriteClips[ 3 ].w = 100;
		gSpriteClips[ 3 ].h = 100; }

	return success; }

void closeSDL() {
	gSpriteSheetTexture.freeSDL(&gSpriteSheetTexture);

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit(); }

int main( int argc, char* args[] ) {
	glue_LTexture(&gSpriteSheetTexture);

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

				gSpriteSheetTexture.renderSDL( &gSpriteSheetTexture, 0, 0, &gSpriteClips[ 0 ] );
				gSpriteSheetTexture.renderSDL( &gSpriteSheetTexture, SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );
				gSpriteSheetTexture.renderSDL( &gSpriteSheetTexture, 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );
				gSpriteSheetTexture.renderSDL( &gSpriteSheetTexture, SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

				SDL_RenderPresent( gRenderer ); }}}

	closeSDL();

	return 0; }



