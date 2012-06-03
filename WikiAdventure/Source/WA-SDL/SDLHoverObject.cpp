
#include "SDLHoverObject.h"
#include "EngineMain.h"

CSDLHoverObject::CSDLHoverObject()
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_bHoverDefaultRect = true;
	m_bFocus = false;
	m_pContainerCallback = 0;

	m_SHoverRect.x = 0; 
	m_SHoverRect.y = 0; 
	m_SHoverRect.h = 0; 
	m_SHoverRect.w = 0;

	/*
	m_SDestRect.x = 0; 
	m_SDestRect.y = 0; 
	m_SDestRect.h = 0; 
	m_SDestRect.w = 0;
	*/
}

CSDLHoverObject::~CSDLHoverObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
	m_bFocus = false;
}

bool CSDLHoverObject::IsPointInRect( int iX, int iY )
{
	if ( m_bVisible == false )
		return false;

	/*
	SDL_Rect* pSRect = 0;

	// Should we use the surface rectangle or the hover rectangle for focus checking?
	if ( m_bHoverDefaultRect == true ) {
		pSRect = &m_SDestRect;
	} else {
		pSRect = &m_SHoverRect;
	}
	*/

	if ( iX <= GetPosX() )					return false;
	if ( iX >= (GetPosX() + GetWidth()) )	return false;
	if ( iY <= GetPosY() )					return false;
	if ( iY >= (GetPosY() + GetHeight()) )	return false;
	return true;
}

bool CSDLHoverObject::LoadImageFromFile( const string& sFile )
{
	bool bResult = CSDLBaseObject::LoadImageFromFile( sFile );

	// If the call succeeded then set the default hovering rectangle
	// to the size of the image (the size of the surface).
	if ( bResult == true )
		m_SHoverRect = m_pSurface->clip_rect;

	return bResult;
}

int CSDLHoverObject::GetWidth()
{
	// Should we use the surface rectangle or the hover rectangle for focus checking?
	if ( m_bHoverDefaultRect == true ) {
		return m_pSurface->clip_rect.w;
	} else {
		return m_SHoverRect.w;
	}
}

int CSDLHoverObject::GetHeight()
{
	// Should we use the surface rectangle or the hover rectangle for focus checking?
	if ( m_bHoverDefaultRect == true ) {
		return m_pSurface->clip_rect.h;
	} else {
		return m_SHoverRect.h;
	}
}

void CSDLHoverObject::Render( SDL_Surface* pDestSurface )
{
	CSDLBaseObject::Render( pDestSurface );

	/*
	m_SDestRect.x = m_iPosX;  
	m_SDestRect.y = m_iPosY;

	if ( m_pSurface == 0 ) {
		// horrible error
		m_SDestRect.w = 50;
		m_SDestRect.h = 50;
	} else {
		m_SDestRect.w = m_pSurface->w;
		m_SDestRect.h = m_pSurface->h;
	}
	*/
	
	if ( pEngine->GetDebugOverlay()->GetShowHighlights() == true ) {
		unsigned int uiColor = SDL_MapRGB( pDestSurface->format, 255, 0, 0 );
		unsigned int uiColor2 = SDL_MapRGB( pDestSurface->format, 100, 0, 0 );
		
		/*
		SDL_Rect* pSRect = 0;

		// Should we use the surface rectangle or the hover rectangle for focus checking?
		if ( m_bHoverDefaultRect == true ) {
			pSRect = &m_pSurface->clip_rect;
		} else {
			pSRect = &m_SHoverRect;
		}
		*/
		SDL_Rect stRect = GetRect();

		Graphics.DrawRect( pDestSurface, stRect, uiColor2, 1 );

		int iPosX = GetPosX();
		int iPosY = GetPosY();
		int iWidth = GetWidth();
		int iHeight = GetHeight();

		long x = iPosX; //pSRect->x;
		long y = iPosY; //pSRect->y;

		for ( ; x < (iPosX + iWidth); ++x )
		{
			if ( (x >= 0 && x < 800) && ((y + iHeight) >= 0 && (y + iHeight) < 600) ) {
				((unsigned int*)pDestSurface->pixels)[ y * (pDestSurface->pitch / 4) + x] = uiColor;
				((unsigned int*)pDestSurface->pixels)[ (y + iHeight) * (pDestSurface->pitch / 4) + x] = uiColor;
			}
		}

		x = iPosX;
		y = iPosY;

		for ( ; y < (iPosY + iHeight); ++y )
		{
			if ( ((x + iWidth) >= 0 && (x + iWidth) < 800) && (y >= 0 && y < 600) ) {
				((unsigned int*)pDestSurface->pixels)[ y * (pDestSurface->pitch / 4) + x ] = uiColor;
				((unsigned int*)pDestSurface->pixels)[ y * (pDestSurface->pitch / 4) + x + iWidth ] = uiColor;
			}
		}
	}
}

void CSDLHoverObject::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	// Store the current value for state change checking
	bool bOldFocus = m_bFocus;

	m_bFocus = false;

	// If the mouse is inside the objects rectangle we are hovering
	if ( IsPointInRect( iX, iY ) == true )
	{
		m_bFocus = true;
		
		// If we didn't have focus last frame then trigger the OnEnter event.
		if ( bOldFocus == false )
		{
			OnMouseEnter();
			// Pass the happy message on to the container, if the callback reference is set
			if ( m_pContainerCallback != 0 )
				m_pContainerCallback->OnEnter( this );
		}

		// We are still hovering.
		OnMouseHovering();
		if ( m_pContainerCallback != 0 )
			m_pContainerCallback->OnHovering( this );
	}
	// We don't have focus now, but did we last frame?
	else if ( bOldFocus == true )
	{
		// We had focus last frame, tell it to the object
		OnMouseLeave();
		// And tell the container that the mouse has left the object.
		if ( m_pContainerCallback != 0 )
			m_pContainerCallback->OnLeave( this );
	}
}

void CSDLHoverObject::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	// The object has to have focus in order to catch a mouse down event.
	// Otherwise the mouse would be outside the objects rectangle.
	if ( m_bFocus == true )
	{
        // button clicked on object
		OnMouseClicked( iButton );
		if ( m_pContainerCallback != 0 )
			m_pContainerCallback->OnClicked( this, iButton );
	}
}
