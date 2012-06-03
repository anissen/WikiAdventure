
#include "Graphics.h"
//#include "Globals.h"

CGraphics::CGraphics()
{

}

CGraphics::~CGraphics()
{

}

void CGraphics::DrawCircle( SDL_Surface* pDestSurface, int x, int y, int r, int c)
{
  int i, j;
  for (i = 0; i < 2 * r; ++i)
  {
    // vertical clipping: (top and bottom)
    if ((y - r + i) >= 0 && (y - r + i) < HEIGHT)
    {
      int len = (int)sqrt((double)(r * r - (r - i) * (r - i))) * 2;
      int xofs = x - len / 2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= WIDTH)
      {
        len -= (xofs + len) - WIDTH;
      }
      int ofs = (y - r + i) * (pDestSurface->pitch / 4) + xofs;
      
      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; ++j)
			DrawPixel( pDestSurface, ofs + j, c);
		  //((unsigned int*)gScreen->pixels)[ofs + j] = c;
    }
  }
  
	/*
	int index = 0;
	for (int xx = 0; xx < 100; xx++) 
	{
		for (int yy = 0; yy < 100; yy++)
		{
			DrawPixel(x+cos(xx)*r,y+sin(yy)*r,c);
		}
	}
	*/
}

unsigned int CGraphics::blend_avg( unsigned int source, unsigned int target )
{
	unsigned int sourcer = (source >>  0) & 0xff;
	unsigned int sourceg = (source >>  8) & 0xff;
	unsigned int sourceb = (source >> 16) & 0xff;
	unsigned int targetr = (target >>  0) & 0xff;
	unsigned int targetg = (target >>  8) & 0xff;
	unsigned int targetb = (target >> 16) & 0xff;

	targetr = (sourcer + targetr) / 2;
	targetg = (sourceg + targetg) / 2;
	targetb = (sourceb + targetb) / 2;

	return (targetr <<  0) |
		(targetg <<  8) |
		(targetb << 16);
}

unsigned int CGraphics::blend_mul( unsigned int source, unsigned int target )
{
	unsigned int sourcer = (source >>  0) & 0xff;
	unsigned int sourceg = (source >>  8) & 0xff;
	unsigned int sourceb = (source >> 16) & 0xff;
	unsigned int targetr = (target >>  0) & 0xff;
	unsigned int targetg = (target >>  8) & 0xff;
	unsigned int targetb = (target >> 16) & 0xff;

	targetr = (sourcer * targetr) >> 8;
	targetg = (sourceg * targetg) >> 8;
	targetb = (sourceb * targetb) >> 8;

	return (targetr <<  0) |
		(targetg <<  8) |
		(targetb << 16);
}

unsigned int CGraphics::blend_add( unsigned int source, unsigned int target )
{
	unsigned int sourcer = (source >>  0) & 0xff;
	unsigned int sourceg = (source >>  8) & 0xff;
	unsigned int sourceb = (source >> 16) & 0xff;
	unsigned int targetr = (target >>  0) & 0xff;
	unsigned int targetg = (target >>  8) & 0xff;
	unsigned int targetb = (target >> 16) & 0xff;

	targetr += sourcer;
	targetg += sourceg;
	targetb += sourceb;

	if (targetr > 0xff) targetr = 0xff;
	if (targetg > 0xff) targetg = 0xff;
	if (targetb > 0xff) targetb = 0xff;

	return (targetr <<  0) |
		(targetg <<  8) |
		(targetb << 16);
}

unsigned int CGraphics::blend_add_half(unsigned int source, unsigned int target)
{
	return blend_add( source / 2, target );
}

void CGraphics::DrawRect( SDL_Surface* pDestSurface, SDL_Rect rect, int c, int b)
{
	DrawRect( pDestSurface, rect.x, rect.y, rect.w, rect.h, c, b );
}

void CGraphics::DrawRect( SDL_Surface* pDestSurface, int x, int y, int width, int height, int c)
{
	DrawRect( pDestSurface, x, y, width, height, c, 0 );
}

void CGraphics::DrawRect( SDL_Surface* pDestSurface, int x, int y, int width, int height, int c, int b)
{
  int i, j;
  for (i = 0; i < height; ++i)
  {
    // vertical clipping: (top and bottom)
    if ((y + i) >= 0 && (y + i) < HEIGHT)
    {
      int len = width;
      int xofs = x;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= WIDTH)
      {
        len -= (xofs + len) - WIDTH;
      }
      int ofs = (i + y) * (pDestSurface->pitch / 4) + xofs;

      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; ++j)
	  {
		  DrawPixel( pDestSurface, ofs + j, c, b, 0);
	  }
    }
  }
}

void CGraphics::DrawPixel( SDL_Surface* pDestSurface, int index, int color, int b, int s )
{
	int pixel = color;
	if (pixel != 0)
	{
		int oldpixel = ((unsigned int*)pDestSurface->pixels)[index];
		switch (b)
		{
		case -1:
			pixel = blend_mul(pixel ^ 0xffffff, oldpixel);
			break;
		case 0:
			pixel = blend_avg(pixel, oldpixel);
			break;
		case 1:
			pixel = blend_add(pixel, oldpixel);
			break;
		case 2:
			pixel = blend_add_half(pixel, oldpixel);
			break;
		}
		((unsigned int*)pDestSurface->pixels)[index] = pixel;        
	}
	//((unsigned int*)gScreen->pixels)[index] = color;
}

void CGraphics::DrawPixel( SDL_Surface* pDestSurface, int index, int color )
{
	((unsigned int*)pDestSurface->pixels)[index] = color;
}

void CGraphics::DrawPixel ( SDL_Surface* pDestSurface, int x, int y, int color)
{
	((unsigned int*)pDestSurface->pixels)[y*(pDestSurface->pitch / 4)+x] = color;
}

