
#include "SDLStateShowText.h"
#include "EngineMain.h"

CSDLStateShowText::CSDLStateShowText( const string& sText, const string& sOnExitScript )
{
	DebugInfo( TypeCreate, "Creating text box." );
	m_sOnExitScript = sOnExitScript;

	m_pText = new CSDLMultilineTextObject( string("Dialog"), sText );
	
	SDL_Color stBlueish = { 100, 100, 255 };
	SDL_Color stWhite	= { 255, 255, 255 };

	m_pButtonOkay = new CSDLCenterTextObject( "GameDefault", "Close", stBlueish, stWhite );

	int iWidth = m_pText->GetWidth();
	int iHeight = m_pText->GetHeight();

	SetPosX( (800 / 2) - (iWidth / 2) );
	SetPosY( (600 / 2) - ((iHeight + 10 + m_pButtonOkay->GetHeight()) / 2) );

	m_pText->SetPos( GetPosX(), GetPosY() );

	int iButtonTop = (m_iPosY + iHeight) + 10;
	if ( (iButtonTop + m_pButtonOkay->GetHeight()) > 600 )
		iButtonTop = 600 - m_pButtonOkay->GetHeight() - 5;

	m_pButtonOkay->SetPos( GetPosX() + iWidth / 2, iButtonTop );
	m_pButtonOkay->SetCallbackContainer( this );

	m_stContainerRect = m_pText->GetRect();
	m_stContainerRect.x -= 5;
	m_stContainerRect.y -= 5;
	m_stContainerRect.w += 10;
	m_stContainerRect.h = m_pButtonOkay->GetButtom() + 5 - m_stContainerRect.y;
}

CSDLStateShowText::~CSDLStateShowText()
{
	DebugInfo( TypeDelete, "Deleting text box." );

	if ( m_pButtonOkay != 0 )
		delete m_pButtonOkay;
	m_pButtonOkay = 0;

	if ( m_sOnExitScript.length() > 0 ) {
		pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnExitScript );
	}
}

void CSDLStateShowText::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseMoved( iButton, iX, iY );
}

void CSDLStateShowText::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateShowText::Render(SDL_Surface* pDestSurface )
{
	//CSDLBaseState::Render( pDestSurface );

	SDL_FillRect( pDestSurface, &m_stContainerRect, 0 );

	m_pText->Render( pDestSurface );
	
	m_pButtonOkay->Render( pDestSurface );
}

void CSDLStateShowText::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( pObject == m_pButtonOkay ) {
		pEngine->GetStateHandler()->DelayedPopLayer();
	}
}