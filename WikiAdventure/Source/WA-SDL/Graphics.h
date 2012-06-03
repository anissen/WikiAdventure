
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_image.h"
#include <math.h>

// Screen width
#define WIDTH 800
// Screen height
#define HEIGHT 600

class CGraphics  
{
private:
	unsigned int blend_avg(unsigned int source, unsigned int target);
	unsigned int blend_add(unsigned int source, unsigned int target);
	unsigned int blend_mul(unsigned int source, unsigned int target);
	unsigned int blend_add_half(unsigned int source, unsigned int target);

public:
	CGraphics();
	virtual ~CGraphics();
	
	void DrawCircle( SDL_Surface* pDestSurface, int x, int y, int r, int c);
	void DrawRect  ( SDL_Surface* pDestSurface, int x, int y, int width, int height, int c);
	void DrawRect  ( SDL_Surface* pDestSurface, int x, int y, int width, int height, int c, int b);
	void DrawRect  ( SDL_Surface* pDestSurface, SDL_Rect rect, int c, int b);
	void DrawTile  ( SDL_Surface* pDestSurface, int x, int y, int tile);
	void DrawPixel ( SDL_Surface* pDestSurface, int index, int color);
	void DrawPixel ( SDL_Surface* pDestSurface, int x, int y, int color);
	void DrawPixel ( SDL_Surface* pDestSurface, int index, int color, int b, int s);
};

#endif // GRAPHICS_H
