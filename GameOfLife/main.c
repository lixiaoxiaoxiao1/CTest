#include "SDL.h"
#include "SDL_image.h"
#include "gfx.h"


//Define window
#define  WINDOW_WIDTH 480 
#define  WINDOW_HEIGHT 320

#define  GRID_SIZE 20  //Cell size
#define  DEF_DENSITY 4  //Density
#define  REF_DELAY 1000

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

//Generate data based on hash Density
void initDensity(int density)
{
	if (density <= 0)density = 1;

	//Iaitialize randomcseed based on time
	srand(time(NULL));

	int i, j, random;
	for (i = 0; i < X_CNT; i++)
	{
		for (j = 0; j < Y_CNT; j++)
		{
			if (i * j == 0 || (i - (X_CNT - 1)) * (j - (Y_CNT - 1)) == 0)
			{
				//Setting Boundaries
				map[i][j] = 0;
			}
			else
			{
				//Generate data based on hash Density
				if ((rand() % 11) <= density)
				{
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
		}
	}
}

////Generate data
void initData()
{
	memset(map, 0, X_CNT * Y_CNT * sizeof(int));
	initDensity(DEF_DENSITY);
	lasttime = SDL_GetTicks();
}
void refStatus()
{
	int i, j, s;
	int u, d, l, r, ul, ur, dl, dr;
	int b[X_CNT][Y_CNT];
	for (i = 0; i < X_CNT; i++)
	{
		for (j = 0; j < Y_CNT; j++)
		{
			b[i][j] = map[i][j];
		}
	}

	for (i = 1; i < X_CNT - 1; i++)
	{
		for (j = 1; j < Y_CNT - 1; j++)
		{
			u = b[i - 1][j];
			d = b[i + 1][j];
			l = b[i][j - 1];
			r = b[i][j + 1];
			ul = b[i - 1][j - 1];
			ur = b[i - 1][j + 1];
			dl = b[i + 1][j - 1];
			dr = b[i + 1][j + 1];
			s = u + d + l + r + ul + ur + dl + dr;

			//¹æÔò
			if (b[i][j] == 1)
			{
				if (s == 2 || s == 3)
				{
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
			else
			{
				if (s == 3)
				{
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
		}
	}
}
//Draw The Info
void draw(SDL_Surface* screen)
{


	int i, j;
	for (i = 0; i < X_CNT; i++)
	{
		for (j = 0; j < Y_CNT; j++)
		{
			if (map[i][j] == 0)
			{
				SDL_fillRect(i * GRID_SIZE, j * GRID_SIZE, GRID_SIZE, GRID_SIZE, toColor32(0, 0, 0));
			}
			else
			{
				SDL_fillRect(i * GRID_SIZE, j * GRID_SIZE, GRID_SIZE, GRID_SIZE, toColor32(100, 0, 100));
			}

		}

	}
	for (i = 0; i < X_CNT; i++)
	{
		SDL_drawLine(i * GRID_SIZE, 0, i * GRID_SIZE, WINDOW_HEIGHT, toColor32(0, 0, 255));
	}
	for (j = 0; j < Y_CNT; j++)
	{
		SDL_drawLine(0, j * GRID_SIZE, WINDOW_WIDTH, j * GRID_SIZE, toColor32(0, 0, 255));
	}



	Uint32 now = SDL_GetTicks();
	if (now - lasttime >= REF_DELAY)
	{
		lasttime = now;
		refStatus();
	}

}