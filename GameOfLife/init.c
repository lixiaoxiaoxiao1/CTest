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
	//initData();

	//Initialize square
		//Draw  square

	//Life reproduction
		//Redraw the square according to the rules of the game
	

	return 0;
}
