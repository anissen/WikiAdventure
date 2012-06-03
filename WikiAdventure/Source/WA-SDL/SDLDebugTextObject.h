
#ifndef SDLDEBUGTEXTOBJECT_H
#define SDLDEBUGTEXTOBJECT_H

#include "SDLBaseTextObject.h"

/** A ? object */
class CSDLDebugTextObject: public CSDLBaseTextObject
{
protected:
	SDL_Color	m_SBGColor;
	SDL_Color	m_SBGHoverColor;

	virtual void CreateTextSurface();

public:
	CSDLDebugTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SBGColor		= stDefBGColor,
		SDL_Color SHoverColor	= stDefBGColor,
		SDL_Color SBGHoverColor	= stDefColor
		);

	virtual ~CSDLDebugTextObject();

	//virtual void Render( SDL_Surface* pDestSurface );
};

#endif // SDLDEBUGTEXTOBJECT_H