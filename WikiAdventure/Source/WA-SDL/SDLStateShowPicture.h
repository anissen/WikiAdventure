
#ifndef SDLSTATESHOWPICTURE_H
#define SDLSTATESHOWPICTURE_H

#include "SDLBaseState.h"

/** A ? object */
class CSDLStateShowPicture: public CSDLBaseState
{
protected:
	CSDLBaseTextObject* m_pButtonOkay;
	SDL_Rect m_stContainerRect;
	string m_sOnExitScript;

public:
	CSDLStateShowPicture( const string& sPicture, const string& sOnExitScript = "" );
	virtual ~CSDLStateShowPicture();

	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
};

#endif // SDLSTATESHOWPICTURE_H