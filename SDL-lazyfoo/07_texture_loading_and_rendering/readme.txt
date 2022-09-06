Copyright Notice:
-----------------
The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.

This project is linked against:
----------------------------------------
Windows:
SDL2
SDL2main
SDL2_image

*nix:
SDL2
SDL2_image

********************* From Lazy Foo *********************
*********************************************************
A major new addition to SDL 2 is the texture rendering API. This gives you fast,
flexible hardware based rendering.

Textures in SDL have their own data type intuitively called an SDL_Texture. When
we deal with SDL textures you need an SDL_Renderer to render it to the screen
which is why we declare a global renderer named "gRenderer".

After we create our window, we have to create a renderer for our window so we
can render textures on it.

After creating the renderer, we want to initialize the rendering color using
SDL_SetRenderDrawColor.

Our texture loading function looks largely the same as before only now instead
of converting the loaded surface to the display format, we create a texture from
the loaded surface using SDL_CreateTextureFromSurface. Like before, this
function creates a new texture from an existing surface which means like before
we have to free the loaded surface and then return the loaded texture.

In the main loop after the event loop, we call SDL_RenderClear. This function
fills the screen with the color that was last set with SDL_SetRenderDrawColor.

With the screen cleared, we render the texture with SDL_RenderCopy. With the
texture rendered, we still have to update the screen, but since we're not using
SDL_Surfaces to render we can't use SDL_UpdateWindowSurface. Instead we have to
use SDL_RenderPresent.

Now, there is a new API call called IMG_LoadTexture. It's not in the official
documentation as of this writing but you can find it in the SDL_image header
files. It allows you to load a texture without having to create a temporary
surface. The reason I haven't gone back and updated the tutorial to use this
method is because I don't want to go back an update 40+ tutorials. Even though
it is undocumented, it works just fine.

*********************************************************


g++ 07_texture_loading_and_rendering.cpp -o 07_texture_loading_and_rendering `sdl2-config --cflags --libs` -lSDL2_image

gcc 07_texture_loading_and_rendering.c -o 07_texture_loading_and_rendering `sdl2-config --cflags --libs` -lSDL2_image



**************************************************************************************************

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

SDL_Init( SDL_INIT_VIDEO )
SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )
gWindow = SDL_CreateWindow(
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


loadMedia():
	gTexture = loadTexture( "texture.png" );


SDL_Texture* loadTexture( char* path ):
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

	SDL_FreeSurface( loadedSurface );

	return newTexture;

loop:
	SDL_RenderClear( gRenderer );
	SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
	SDL_RenderPresent( gRenderer );



