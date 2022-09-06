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



gcc 08_geometry_rendering.c -o 08_geometry_rendering `sdl2-config --cflags --libs` -lSDL2_image









SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Init( SDL_INIT_VIDEO )
SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )

gWindow = SDL_CreateWindow(
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );




********************************
NOTES:
You deal with the gRenderer.


