#pragma once


#define toColor32(r,g,b) (r<<16|g<<8|b)


//define method
#pragma once


void SDL_putpixel(int x, int y, int color);
void SDL_drawLine(int sx, int sy, int dx, int dy, int color);
void SDL_fillRect(int x, int y, int w, int h, int color);