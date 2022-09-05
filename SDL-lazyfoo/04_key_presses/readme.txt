Copyright Notice:
-----------------
The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.

This project is linked against:
----------------------------------------
Windows:
SDL2
SDL2main

*nix:
SDL2






gcc 04_key_presses.c -o 04_key_presses `sdl2-config --cflags --libs` -lSDL2_image





*****************************************************************************************
Pattern:
******************
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

SDL_Init( SDL_INIT_VIDEO )
gwindow = SDL_CreateWindow(
gScreenSurface = SDL_GetWindowSurface( gWindow );

gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );

SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

SDL_UpdateWindowSurface( gWindow );

===========
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL };

SDL_Surface* loadSurface( char* );

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];
SDL_Surface* gCurrentSurface = NULL;

SDL_Init( SDL_INIT_VIDEO )
gWindow = SDL_CreateWindow(
gScreenSurface = SDL_GetWindowSurface( gWindow );

gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "press.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "up.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "down.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "left.bmp" );
gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "right.bmp" );










