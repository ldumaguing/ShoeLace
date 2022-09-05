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






gcc 02_getting_an_image_on_the_screen.c -o 02_getting_an_image_on_the_screen `sdl2-config --cflags --libs` -lSDL2_image


Notes:
I made the window bigger (800x600).  The graphic file didn't stretch.



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












