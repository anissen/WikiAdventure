
#ifndef SDLCENTERTEXTOBJECT_H
#define SDLCENTERTEXTOBJECT_H

#include "SDLBaseTextObject.h"

/** A ? object */
class CSDLCenterTextObject: public CSDLBaseTextObject
{
protected:
	int	m_iOrgPosX;

public:
	CSDLCenterTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SHoverColor	= stDefBGColor
		);

	virtual ~CSDLCenterTextObject();

	virtual void SetPosX( int iPosX );
	virtual void Render( SDL_Surface* pDestSurface );
};

#endif // SDLCENTERTEXTOBJECT_H