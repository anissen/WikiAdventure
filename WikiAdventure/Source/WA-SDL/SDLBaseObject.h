
#ifndef SDLBASEOBJECT_H
#define SDLBASEOBJECT_H

#include "SDLBaseInterface.h"
#include "Globals.h"

/** Base SDL screen object */
class CSDLBaseObject: public ISDLBaseInterface
{
protected:
	int				m_iPosX;
	int				m_iPosY;
	SDL_Surface*	m_pSurface;
	bool			m_bVisible;
	int				m_iAlpha;

public:
	CSDLBaseObject();
	virtual ~CSDLBaseObject();

	virtual bool LoadImageFromFile( const string& sFile);

	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void SetPosX( int iPosX )	{ m_iPosX = iPosX; };
	virtual int  GetPosX()				{ return m_iPosX; };
	virtual void SetPosY( int iPosY )	{ m_iPosY = iPosY; };
	virtual int  GetPosY()				{ return m_iPosY; };
	virtual void SetPos( int iPosX, int iPosY ) { SetPosX( iPosX ); SetPosY( iPosY ); };

	virtual SDL_Rect GetRect();

	virtual int GetHeight() { return m_pSurface->h; }
	virtual int GetWidth()	{ return m_pSurface->w; }
	virtual int GetButtom() { return GetPosY() + GetHeight(); }

	virtual void SetAlpha( int iAlpha ) { m_iAlpha = iAlpha; }
	virtual int GetAlpha() { return m_iAlpha; }

	virtual void SetVisible( bool bVisible ) { m_bVisible = bVisible; }
	virtual bool GetVisible() { return m_bVisible; }
};

#endif // SDLBASEOBJECT_H