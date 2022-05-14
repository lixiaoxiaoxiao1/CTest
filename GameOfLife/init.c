#include "SDL.h"
#include "SDL_image.h"
#include "gfx.h"



//The rules of the game
static SDL_Surface* halscreen, * buffer_screen;
static SDL_Rect winSize;
#define _VIDEO_BPP 32

//Draw squares

SDL_Rect getWindowsSize();
void initData();
int main(int argc, char *argv[])
{
	//Initialization window
	int    done;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG);

	winSize = getWindowsSize();
	initData();

	//Initialize square
	halscreen = SDL_SetVideoMode(winSize.w, winSize.h, 0, 0);
	buffer_screen = SDL_CreateRGBSurface(0, winSize.w, winSize.h, _VIDEO_BPP, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = winSize.w;
	rect.h = winSize.h;
		//Draw  square

	//Life reproduction
		//Redraw the square according to the rules of the game
	

	return 0;
}
