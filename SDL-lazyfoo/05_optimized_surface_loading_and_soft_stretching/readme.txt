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








gcc 05_optimized_surface_loading_and_soft_stretching.c -o 05_optimized_surface_loading_and_soft_stretching `sdl2-config --cflags --libs` -lSDL2_image








SDL_Surface* loadSurface( char* path ) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP( path );
	optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );

	return optimizedSurface; }
	
	
	
	
	
	
	
