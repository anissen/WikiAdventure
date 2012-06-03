
#ifndef SDLHOVEROBJECT_H
#define SDLHOVEROBJECT_H

#include "SDLBaseObject.h"
#include "SDLUIContainerInterface.h"

/** A ? object */
class CSDLHoverObject: public CSDLBaseObject
{
protected:
	ISDLUIContainerInterface* m_pContainerCallback;
	bool		m_bHoverDefaultRect;
	//SDL_Rect	m_SDestRect;
	SDL_Rect	m_SHoverRect;
	bool		m_bFocus;

	bool IsPointInRect( int iX, int iY );

public:
	CSDLHoverObject();
	virtual ~CSDLHoverObject();

	virtual bool LoadImageFromFile( const string& sFile );
	virtual void Render( SDL_Surface* pDestSurface  );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void SetCallbackContainer( ISDLUIContainerInterface* pContainerCallback ) { m_pContainerCallback = pContainerCallback; }
	virtual ISDLUIContainerInterface* GetCallbackContainer() { return m_pContainerCallback; }

	virtual void OnMouseEnter	() {};
	virtual void OnMouseLeave	() {};
	virtual void OnMouseHovering() {};
	virtual void OnMouseClicked	( const int& iButton ) {};

	virtual int GetHeight();
	virtual int GetWidth();

	virtual bool GetFocus() { return m_bFocus; }
	virtual void SetFocus( bool bFocus ) { m_bFocus = bFocus; } // HACK! 

	virtual void SetHoverRect( SDL_Rect SHoverRect ) { m_SHoverRect = SHoverRect; }

	virtual void SetHoverDefaultRect( bool bHoverDefaultRect ) { m_bHoverDefaultRect = bHoverDefaultRect; }
	virtual bool GetHoverDefaultRect() { return m_bHoverDefaultRect; }
};

#endif // SDLHOVEROBJECT_H