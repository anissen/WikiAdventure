
#ifndef SDLSTATESHOWTEXT_H
#define SDLSTATESHOWTEXT_H

#include "SDLBaseState.h"
#include "SDLMultilineTextObject.h"

/** A ? object */
class CSDLStateShowText: public CSDLBaseState
{
protected:
	CSDLMultilineTextObject* m_pText;
	CSDLBaseTextObject* m_pButtonOkay;
	SDL_Rect m_stContainerRect;
	string m_sOnExitScript;

public:
	CSDLStateShowText( const string& sText, const string& sOnExitScript = "" );
	virtual ~CSDLStateShowText();

	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
};

#endif // SDLSTATESHOWTEXT_H