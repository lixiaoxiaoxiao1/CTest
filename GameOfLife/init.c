#include "SDL.h"
#include "SDL_image.h"
#include "gfx.h"

//The rules of the game
static SDL_Surface* halscreen, * buffer_screen;
static SDL_Rect winSize;
#define _VIDEO_BPP 32

void SDL_putpixel(int x, int y, int color)
{
	switch (_VIDEO_BPP)
	{
	case 32:
	{
		unsigned int* dest = (unsigned int*)(buffer_screen->pixels);
		dest += (x + y * buffer_screen->w);
		*dest = color;
	}
	break;
	case 16:
	{
		int r, g, b;
		r = ((color & 0xff0000) >> 16);
		g = ((color & 0x00ff00) >> 8);
		b = ((color & 0x0000ff));
		unsigned short* dest = (unsigned short*)(buffer_screen->pixels);
		dest += (x + y * buffer_screen->w);
		*dest = (((r << 8) & 0xf800) | ((g << 3) & 0x7e0) | ((b >> 3) & 0x1f));
	}
	break;

	}
}

void SDL_drawLine(int sx, int sy, int dx, int dy, int color)
{
	int width = buffer_screen->w;
	int height = buffer_screen->h;

	int sx1 = (int)((sx));
	int sy1 = (int)((sy));
	int dx1 = (int)((dx));
	int dy1 = (int)((dy));

	if (sy1 < 0)sy1 = 0;
	if (dy1 < 0)dy1 = 0;
	if (sy1 >= height)sy1 = height - 1;
	if (dy1 >= height)dy1 = height - 1;

	if (sx1 < 0)sx1 = 0;
	if (sx1 >= width)sx1 = width - 1;
	if (dx1 < 0)dx1 = 0;
	if (dx1 >= width)dx1 = width - 1;
	//=============================================================

	int t, dis;
	int x = 0, y = 0, delta_x, delta_y, incx, incy;
	delta_x = dx - sx;
	delta_y = dy - sy;
	if (delta_x > 0)incx = 1;
	else if (delta_x == 0)incx = 0;
	else { delta_x = -delta_x; incx = -1; }
	if (delta_y > 0)incy = 1;
	else if (delta_y == 0)incy = 0;
	else { delta_y = -delta_y; incy = -1; }
	if (delta_x > delta_y)
		dis = delta_x;
	else
		dis = delta_y;

	for (t = 0; t < dis + 2; t++)
	{
		SDL_putpixel(sx, sy, color);
		x += delta_x;
		y += delta_y;
		if (x > dis)
		{
			x -= dis;
			sx += incx;
		}
		if (y > dis)
		{
			y -= dis;
			sy += incy;
		}
	}
}

void SDL_fillRect(int x, int y, int w, int h, int color)
{
	int xx = x, yy = y, ww = w, hh = h;
	if (x < 0)
	{
		w += x;
		x = 0;
	}
	if (y < 0)
	{
		h += y;
		y = 0;
	}
	if (w <= 0 || h <= 0)return;

	for (int yy = 0; yy < h; yy++)
	{
		SDL_drawLine(x, y + yy, x + w - 1, y + yy, color);
	}

}



//Draw squares

extern void draw(SDL_Surface*);
extern SDL_Rect getWindowsSize();
extern void initData();
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
	//Draw  square
	halscreen = SDL_SetVideoMode(winSize.w, winSize.h, 0, 0);
	buffer_screen = SDL_CreateRGBSurface(0, winSize.w, winSize.h, _VIDEO_BPP, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = winSize.w;
	rect.h = winSize.h;
		
	SDL_Event event;
	int gameRunning = 1;
	//Life reproduction
		//Redraw the square according to the rules of the game
	while (gameRunning)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = 0;
				break;
			}
		}
		if (SDL_MUSTLOCK(halscreen))
		{
			SDL_LockSurface(halscreen);
		}

		draw(buffer_screen);

		SDL_BlitSurface(buffer_screen, &rect, halscreen, &rect);
		if (halscreen->flags & SDL_DOUBLEBUF)
		{
			SDL_Flip(halscreen);
		}
		else
		{
			SDL_UpdateRect(halscreen, 0, 0, 0, 0);
		}
		if (SDL_MUSTLOCK(halscreen))
		{
			SDL_UnlockSurface(halscreen);
		}
	}




	SDL_Quit();

	
	

	return 0;
}
