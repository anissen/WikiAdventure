
#include "SDLDebugTextObject.h"

CSDLDebugTextObject::CSDLDebugTextObject( const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SBGColor, SDL_Color SHoverColor, SDL_Color SBGHoverColor): CSDLBaseTextObject( sFontID, sText, SColor, SHoverColor ), m_SBGColor( SBGColor ), m_SBGHoverColor( SBGHoverColor ) 
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );

	m_iAlpha = 150;

	CreateTextSurface();
}

CSDLDebugTextObject::~CSDLDebugTextObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
}


void CSDLDebugTextObject::CreateTextSurface()
{
	if ( (m_pFont == 0) || (m_iAlpha == 0) ) return; //If theres no font or its 100% transparent.

	SDL_FreeSurface( m_pSurface );

	if ( m_bFocus == true ) {
		m_pSurface = TTF_RenderText_Shaded( m_pFont, GetText().c_str(), m_SHoverColor, m_SBGHoverColor );
	} else {
		m_pSurface = TTF_RenderText_Shaded( m_pFont, GetText().c_str(), m_SColor, m_SBGColor );
	}

	if( m_pSurface == 0 )
	{
		//handle error here, perhaps print TTF_GetError at least
		return;
	}
}

/*
void CSDLDebugTextObject::Render( SDL_Surface* pDestSurface )
{
	if ( (m_pFont == 0) || (m_iAlpha == 0) ) return; //If theres no font or its 100% transparent.

	SDL_FreeSurface( m_pSurface );

	if ( m_bFocus == true ) {
		m_pSurface = TTF_RenderText_Shaded( m_pFont, GetText().c_str(), m_SHoverColor, m_SBGHoverColor );
	} else {
		m_pSurface = TTF_RenderText_Shaded( m_pFont, GetText().c_str(), m_SColor, m_SBGColor );
	}

	if( m_pSurface == 0 )
	{
		//handle error here, perhaps print TTF_GetError at least
		return;
	}

	CSDLHoverObject::Render( pDestSurface );
}
*/