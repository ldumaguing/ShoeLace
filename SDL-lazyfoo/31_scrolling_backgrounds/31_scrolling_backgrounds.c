#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

typedef struct {
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
		
	#if defined(SDL_TTF_MAJOR_VERSION)
	bool loadFromRenderedText( char*, SDL_Color );
	#endif

	bool ( *loadFromFile )( void*, char* );
	void ( *free )(void*);
	void ( *setColor )( void*, Uint8, Uint8, Uint8 );
	void ( *setBlendMode )( void*, SDL_BlendMode );
	void ( *setAlpha )( void*, Uint8 );
	void ( *render )( void*, int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip );
	int ( *getWidth )(void*);
	int ( *getHeight )(void*); } LTexture;

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

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture__loadFromRenderedText( void* self, char* textureText, SDL_Color textColor ) {
	((LTexture *)self)->free(self);

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText, textColor );
	if( textSurface != NULL ) {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( ((LTexture *)self)->mTexture == NULL ) {
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); }
		else {
			((LTexture *)self)->mWidth = textSurface->w;
			((LTexture *)self)->mHeight = textSurface->h; }

		SDL_FreeSurface( textSurface ); }
	else {
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); }
	
	return ((LTexture *)self)->mTexture != NULL; }
#endif

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

void LTexture__render( void* self, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { x, y, ((LTexture *)self)->mWidth, ((LTexture *)self)->mHeight };

	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h; }

	SDL_RenderCopyEx( gRenderer, ((LTexture *)self)->mTexture, clip, &renderQuad, angle, center, flip ); }

int LTexture__getWidth( void* self) {
	return ((LTexture *)self)->mWidth; }

int LTexture__getHeight( void* self ) {
	return ((LTexture *)self)->mHeight; }

// ***********************************************
typedef struct {
	int DOT_WIDTH;  // = 20;
	int DOT_HEIGHT; // = 20;
	int DOT_VEL;    // = 10;

	int mPosX, mPosY;
	int mVelX, mVelY;

	void ( *handleEvent )( void*, SDL_Event* e );
	void ( *move )(void*);
	void ( *render )(void*, LTexture*); } Dot;

void Dot__handleEvent( void* self, SDL_Event* e ) {
	if( e->type == SDL_KEYDOWN && e->key.repeat == 0 ) {
		switch( e->key.keysym.sym ) {
			case SDLK_UP: ((Dot *)self)->mVelY -= ((Dot *)self)->DOT_VEL; break;
			case SDLK_DOWN: ((Dot *)self)->mVelY += ((Dot *)self)->DOT_VEL; break;
			case SDLK_LEFT: ((Dot *)self)->mVelX -= ((Dot *)self)->DOT_VEL; break;
			case SDLK_RIGHT: ((Dot *)self)->mVelX += ((Dot *)self)->DOT_VEL; break; }}
	else if( e->type == SDL_KEYUP && e->key.repeat == 0 ) {
		switch( e->key.keysym.sym ) {
			case SDLK_UP: ((Dot *)self)->mVelY += ((Dot *)self)->DOT_VEL; break;
			case SDLK_DOWN: ((Dot *)self)->mVelY -= ((Dot *)self)->DOT_VEL; break;
			case SDLK_LEFT: ((Dot *)self)->mVelX += ((Dot *)self)->DOT_VEL; break;
			case SDLK_RIGHT: ((Dot *)self)->mVelX -= ((Dot *)self)->DOT_VEL; break; }}}

void Dot__move(void* self) {
    ((Dot *)self)->mPosX += ((Dot *)self)->mVelX;

    if( ( ((Dot *)self)->mPosX < 0 ) || ( ((Dot *)self)->mPosX + ((Dot *)self)->DOT_WIDTH > SCREEN_WIDTH ) ) {
        ((Dot *)self)->mPosX -= ((Dot *)self)->mVelX; }

    ((Dot *)self)->mPosY += ((Dot *)self)->mVelY;

    if( ( ((Dot *)self)->mPosY < 0 ) || ( ((Dot *)self)->mPosY + ((Dot *)self)->DOT_HEIGHT > SCREEN_HEIGHT ) ) {
        ((Dot *)self)->mPosY -= ((Dot *)self)->mVelY; }}

void Dot__render(void* dot, LTexture* dot_texture) {
	LTexture__render(
		dot_texture,
		((Dot *)dot)->mPosX,
		((Dot *)dot)->mPosY,
		NULL,
		0.0,
		NULL,
		0); }

void glue_LTexture(LTexture* X) {

	#if defined(SDL_TTF_MAJOR_VERSION)
	X->loadFromRenderedText = &LTexture__loadFromRenderedText;
	#endif

	X->loadFromFile = &LTexture__loadFromFile;
	X->free = &LTexture__free;
	X->setColor = &LTexture__setColor;
	X->setBlendMode = &LTexture__setBlendMode;
	X->setAlpha = &LTexture__setAlpha;
	X->render = &LTexture__render;
	X->getWidth = &LTexture__getWidth;
	X->getHeight = &LTexture__getHeight; }

void glue_Dot(Dot* X){
	X->handleEvent = &Dot__handleEvent;
	X->move = &Dot__move;
	X->render = &Dot__render; }

// ***************************************************************************************
LTexture gDotTexture;
LTexture gBGTexture;

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

	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
	if( !gDotTexture.loadFromFile( &gDotTexture, "dot.bmp" ) ) {
		printf( "Failed to load dot texture!\n" );
		return false; }

	if( !gBGTexture.loadFromFile( &gBGTexture, "bg.png" ) ) {
		printf( "Failed to load background texture!\n" );
		return false; }

	return true; }

void closeSDL() {
	gDotTexture.free(&gDotTexture);
	gBGTexture.free(&gBGTexture);

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit(); }

// ***************************************************************************************
int main( int argc, char* args[] ) {
	glue_LTexture(&gDotTexture);
	glue_LTexture(&gBGTexture);

	if( !init() ) {
		printf( "Failed to initialize!\n" );
		return 1; }

	if( !loadMedia() ) {
		printf( "Failed to load media!\n" );
		return 1; }

	bool quit = false;
	SDL_Event e;

	Dot dot;
	glue_Dot(&dot);

	dot.DOT_WIDTH = 20;
	dot.DOT_HEIGHT = 20;
	dot.DOT_VEL = 10;
	dot.mPosX = 0;
	dot.mPosY = 0;
	dot.mVelX = 0;
	dot.mVelY = 0;

	int scrollingOffset = 0;

	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true; }
			dot.handleEvent( &dot, &e ); 
			}

		dot.move( &dot );

		--scrollingOffset;
		if( scrollingOffset < -gBGTexture.getWidth(&gBGTexture) ) {
			scrollingOffset = 0; }

		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		gBGTexture.render( &gBGTexture, scrollingOffset, 0, NULL, 0.0, NULL, 0 );
		gBGTexture.render( &gBGTexture, scrollingOffset + gBGTexture.getWidth(&gBGTexture), 0, NULL, 0.0, NULL, 0 );

		dot.render(&dot, &gDotTexture);

		SDL_RenderPresent( gRenderer ); }

	closeSDL();

	return 0;
}



