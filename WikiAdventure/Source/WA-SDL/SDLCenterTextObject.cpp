
#include "SDLCenterTextObject.h"

CSDLCenterTextObject::CSDLCenterTextObject( const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SHoverColor )
: CSDLBaseTextObject( sFontID, sText, SColor, SHoverColor )
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	//m_iOrgPosX = m_iPosX;

	// Make sure the x-position is correctly calculated
	//SetText( sText );
}

CSDLCenterTextObject::~CSDLCenterTextObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
}

void CSDLCenterTextObject::SetPosX(int iPosX )
{
	m_iOrgPosX = iPosX;
	CSDLBaseTextObject::SetPosX( iPosX );
}

void CSDLCenterTextObject::Render( SDL_Surface* pDestSurface )
{
	int iW = 0;
	int iH = 0;
	TTF_SizeText( m_pFont, GetText().c_str(), &iW, &iH );
	m_iPosX = m_iOrgPosX - iW / 2;

	CSDLBaseTextObject::Render( pDestSurface );
}