#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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
	void ( *render )(void*); } Dot;
/*
Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
*/

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

void Dot__render(void* self) {
	gDotTexture.render( ((Dot *)self)->mPosX, ((Dot *)self)->mPosY ); }

void glue_LTexture(LTexture* X) {

	#if defined(SDL_TTF_MAJOR_VERSION)
	X->loadFromRenderedText = &loadFromRenderedText;
	#endif

	X->loadFromFile = &loadFromFile;
	X->free = &free;
	X->setColor = &setColor;
	X->setBlendMode = &setBlendMode;
	X->setAlpha = &setAlpha;
	X->render = &render;
	X->getWidth = &getWidth;
	X->getHeight = &getHeight; }

// ***************************************************************************************
LTexture gDotTexture;
LTexture gBGTexture;

bool init() {
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false; }
	else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" ); }

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false; }
		else {
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false; }
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; }}}}

	return success; }

bool loadMedia() {
	bool success = true;

	if( !gDotTexture.loadFromFile( "dot.bmp" ) ) {
		printf( "Failed to load dot texture!\n" );
		success = false; }

	if( !gBGTexture.loadFromFile( "bg.png" ) ) {
		printf( "Failed to load background texture!\n" );
		success = false; }

	return success; }

void closeSDL() {
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit(); }

int main( int argc, char* args[] ) {
	glue_LTexture(&gDotTexture);
	glue_LTexture(&gBGTexture);

	if( !init() ) {
		printf( "Failed to initialize!\n" ); }
	else {
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" ); }
		else {
			bool quit = false;
			SDL_Event e;
			Dot dot;

			int scrollingOffset = 0;

			while( !quit ) {
				while( SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT ) {
						quit = true; }
					dot.handleEvent( e ); }

				dot.move();

				--scrollingOffset;
				if( scrollingOffset < -gBGTexture.getWidth() ) {
					scrollingOffset = 0; }

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

				dot.render();

				SDL_RenderPresent( gRenderer ); }}}

	closeSDL();

	return 0;
}



