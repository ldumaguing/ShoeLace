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






gcc 01_hello_SDL.c -o 01_hello_SDL `sdl2-config --cflags --libs`





*****************************************************************************************
Pattern:
******************
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Init( SDL_INIT_VIDEO )
window = SDL_CreateWindow(
screenSurface = SDL_GetWindowSurface( window )
SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
SDL_UpdateWindowSurface( window );




