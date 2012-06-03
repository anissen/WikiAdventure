
#ifndef SDLBASETEXTOBJECT_H
#define SDLBASETEXTOBJECT_H

#include "SDLHoverObject.h"
#include "SDL_ttf.h"

static SDL_Color stDefColor   = { 255, 255, 255 };
static SDL_Color stDefBGColor = { 0, 0, 0 };

/** A ? object */
class CSDLBaseTextObject: public CSDLHoverObject
{
private:
	string		m_sText;

protected:
	TTF_Font*	m_pFont;
	SDL_Color	m_SColor;
	SDL_Color	m_SHoverColor;

	virtual void CreateTextSurface();

public:
	CSDLBaseTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SHoverColor	= stDefBGColor
		);

	virtual ~CSDLBaseTextObject();

	void	SetText	( const string& sText );
	string	GetText	()	{ return m_sText; }

	virtual void Render( SDL_Surface* pDestSurface );

	virtual void OnMouseEnter	();
	virtual void OnMouseLeave	();
	virtual void OnMouseClicked	( const int& iButton ) {};
};

#endif // SDLBASETEXTOBJECT_H