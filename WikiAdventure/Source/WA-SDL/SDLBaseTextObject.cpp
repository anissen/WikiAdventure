
#include "SDLBaseTextObject.h"

CSDLBaseTextObject::CSDLBaseTextObject( const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SHoverColor )
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_pFont = FontHandler.GetFont( sFontID );
	m_sText = "[Nothing]";
	m_bFocus = false;

	m_SColor = SColor;
	m_SHoverColor = SHoverColor;

	// Make sure a surface is created
	SetText( sText );
}

CSDLBaseTextObject::~CSDLBaseTextObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
	SDL_FreeSurface( m_pSurface );
}

void CSDLBaseTextObject::SetText( const string& sText )
{
	if ( sText == m_sText )
		return;

	if ( sText.length() == 0 ) {
		m_sText = " ";
	} else {
		m_sText = sText;
	}

	CreateTextSurface();
}

// A little bit of optimization instead of use creating the surface in the Render() function.
void CSDLBaseTextObject::CreateTextSurface()
{
	if (m_pFont == 0) {
		m_sText = "Text object dosn't have a font!";
		return;
	}

	if (m_iAlpha == 0) 
		return; //It's 100% transparent.

	SDL_FreeSurface( m_pSurface );

	if ( m_bFocus == true ) {
		m_pSurface = TTF_RenderText_Blended( m_pFont, m_sText.c_str(), m_SHoverColor );
	} else {
		m_pSurface = TTF_RenderText_Blended( m_pFont, m_sText.c_str(), m_SColor );
	}

	if( m_pSurface == 0 )
	{
		//handle error here, perhaps print TTF_GetError at least
		int x = 5;
		return;
	}
}

void CSDLBaseTextObject::Render( SDL_Surface* pDestSurface )
{
	CSDLHoverObject::Render( pDestSurface );
}

void CSDLBaseTextObject::OnMouseEnter()
{
	CSDLHoverObject::OnMouseEnter();
	CreateTextSurface();
}

void CSDLBaseTextObject::OnMouseLeave()
{
	CSDLHoverObject::OnMouseLeave();
	CreateTextSurface();
}