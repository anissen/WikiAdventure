
#ifndef SDLMULTILINETEXTOBJECT_H
#define SDLMULTILINETEXTOBJECT_H

#include "SDLBaseTextObject.h"
#include "SDLDebugTextObject.h"
#include "SDLTextSelectionList.h"
#include "SDLCenterTextObject.h"

/** A ? object */
class CSDLMultilineTextObject: public CSDLTextSelectionList
{
protected:
	string		m_sFont;
	SDL_Color	m_stColor;
	SDL_Color	m_stHoverColor;
	int			m_iMaxWidth;

	// HACKY HACKY HACK!
	CSDLMultilineTextObject( 
		bool bDoNotSetText,
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SHoverColor	= stDefBGColor,
		int iMaxWidth			= 600
		);

public:
	CSDLMultilineTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SHoverColor	= stDefBGColor,
		int iMaxWidth			= 600
	);

	virtual ~CSDLMultilineTextObject();

	virtual void SetText( const string& sText );
	//virtual void GetText() { return CSDLTextSelectionList:: }

	virtual void Render( SDL_Surface* pDestSurface );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void OnMouseEnter();
	virtual void OnMouseLeave();

	virtual void AddTextLineObject( const string& sText );
};

/** A ? object */
class CSDLMultilineCenterTextObject: public CSDLMultilineTextObject
{
public:
	CSDLMultilineCenterTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SHoverColor	= stDefBGColor,
		int iMaxWidth			= 600
		)
		: CSDLMultilineTextObject( sFontID, sText, SColor, SHoverColor, iMaxWidth ) {};

	virtual ~CSDLMultilineCenterTextObject() {};

	//virtual void SetText( const string& sText );

	virtual void AddTextLineObject( const string& sText )
	{
		AddObject( new CSDLCenterTextObject( m_sFont, sText, m_stColor, m_stHoverColor ) );
	}
};

/** A ? object */
class CSDLMultilineDebugTextObject: public CSDLMultilineTextObject
{
protected:
	SDL_Color m_stBGColor;
	SDL_Color m_stBGHoverColor;

public:
	CSDLMultilineDebugTextObject( 
		const string& sFontID, 
		const string& sText		= "Hello World", 
		SDL_Color SColor		= stDefColor, 
		SDL_Color SBGColor		= stDefBGColor,
		SDL_Color SHoverColor	= stDefBGColor,
		SDL_Color SBGHoverColor	= stDefColor,
		int iMaxWidth			= 600
		);

	virtual ~CSDLMultilineDebugTextObject();

	virtual void AddTextLineObject( const string& sText );
};

#endif // SDLMULTILINETEXTOBJECT_H