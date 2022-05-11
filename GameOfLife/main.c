#include "SDL.h"
#include "SDL_image.h"
#include "gfx.h"


//Define window
#define  WINDOW_WIDTH 480 
#define  WINDOW_HEIGHT 320

#define  GRID_SIZE 20  //Cell size
#define  DEF_DENSITY 4  //Density

#define X_CNT (WINDOW_WIDTH/GRID_SIZE) 
#define Y_CNT (WINDOW_HEIGHT/GRID_SIZE)

//Computational cell multiplication

static int map[X_CNT][Y_CNT];
static Uint32 lasttime = 0;

SDL_Rect getWindowsSize()
{
	SDL_Rect s;
	s.w = WINDOW_WIDTH;
	s.h = WINDOW_HEIGHT;
	s.x = 0;
	s.y = 0;

	return s;
}