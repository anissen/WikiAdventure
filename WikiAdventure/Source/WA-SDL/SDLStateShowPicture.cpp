
#include "SDLStateShowPicture.h"
#include "EngineMain.h"

CSDLStateShowPicture::CSDLStateShowPicture( const string& sPicture, const string& sOnExitScript )
{
	DebugInfo( TypeCreate, "Creating picture box." );

	m_sOnExitScript = sOnExitScript;

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), sPicture ) );
	
	SDL_Color stBlueish = { 100, 100, 255 };
	SDL_Color stWhite	= { 255, 255, 255 };

	m_pButtonOkay = new CSDLCenterTextObject( "GameDefault", "Close", stBlueish, stWhite );

	int iWidth = m_pBackground->GetWidth();
	int iHeight = m_pBackground->GetHeight();

	SetPosX( (800 / 2) - (iWidth / 2) );
	SetPosY( (600 / 2) - ((iHeight + 10 + m_pButtonOkay->GetHeight()) / 2) );

	m_pBackground->SetPos( GetPosX(), GetPosY() );

	int iButtonTop = (m_iPosY + iHeight) + 5;
	if ( (iButtonTop + m_pButtonOkay->GetHeight()) > 600 )
		iButtonTop = 600 - m_pButtonOkay->GetHeight() - 5;

	m_pButtonOkay->SetPos( GetPosX() + iWidth / 2, iButtonTop );
	m_pButtonOkay->SetCallbackContainer( this );

	m_stContainerRect = m_pBackground->GetRect();
	m_stContainerRect.x -= 5;
	m_stContainerRect.y -= 5;
	m_stContainerRect.w += 10;
	m_stContainerRect.h = m_pButtonOkay->GetButtom() + 5 - m_stContainerRect.y;
}

CSDLStateShowPicture::~CSDLStateShowPicture()
{
	DebugInfo( TypeDelete, "Deleting picture box." );

	if ( m_pButtonOkay != 0 )
		delete m_pButtonOkay;
	m_pButtonOkay = 0;

	if ( m_sOnExitScript.length() > 0 ) {
		pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnExitScript );
	}
}

void CSDLStateShowPicture::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseMoved( iButton, iX, iY );
}

void CSDLStateShowPicture::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateShowPicture::Render(SDL_Surface* pDestSurface )
{
	//CSDLBaseState::Render( pDestSurface );

	SDL_FillRect( pDestSurface, &m_stContainerRect, 0 );

	m_pBackground->Render( pDestSurface );
	
	m_pButtonOkay->Render( pDestSurface );
}

void CSDLStateShowPicture::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( pObject == m_pButtonOkay ) {
		pEngine->GetStateHandler()->DelayedPopLayer();
	}
}