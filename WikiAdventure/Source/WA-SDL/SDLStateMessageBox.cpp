
#include "SDLStateMessageBox.h"
#include "EngineMain.h"

CSDLStateMessageBox::CSDLStateMessageBox( const string& sTitle, const string& sMessage )
{
	InitMsgBox( sTitle, sMessage );
}

CSDLStateMessageBox::CSDLStateMessageBox( const string& sTitle, const string& sMessage, const string& sOnExitScript )
{
	m_sOnExitScript = sOnExitScript;
	InitMsgBox( sTitle, sMessage );
}

void CSDLStateMessageBox::InitMsgBox( const string& sTitle, const string& sMessage )
{
	DebugInfo( TypeCreate, "Creating message box." );

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "Box.png" ) );

	this->SetAlpha( 230 );
	m_pBackground->SetAlpha( GetAlpha() );

	int iWidth = m_pBackground->GetWidth();
	int iHeight = m_pBackground->GetHeight();

	SetPosX( (800 / 2) - (iWidth / 2) );
	SetPosY( (600 / 2) - (iHeight / 2) );

	m_pBackground->SetPos( GetPosX(), GetPosY() );

	SDL_Color stBlueBlack = { 50, 50, 125 };
	SDL_Color stBlueish = { 100, 100, 255 };
	SDL_Color stBlack = { 0, 0, 0 };

	m_pTitle = new CSDLBaseTextObject( "GameDefaultLarge", sTitle , stBlueBlack );
	m_pTitle->SetPos( GetPosX() + 8, GetPosY() + 10 );
	m_pTitle->SetAlpha( GetAlpha() );

	m_pMessage = new CSDLMultilineTextObject( "Dialog", sMessage, stBlack, stBlack, iWidth - 16 );
	m_pMessage->SetPos( GetPosX() + 8, m_pTitle->GetButtom() + 10 );
	m_pMessage->SetAlpha( GetAlpha() );

	m_pButtonOkay = new CSDLBaseTextObject( "GameDefault", "Close", stBlueish );
	m_pButtonOkay->SetPos( GetPosX() + iWidth - m_pButtonOkay->GetWidth() - 30 , (m_iPosY + iHeight) - m_pButtonOkay->GetHeight() - 9 );
	m_pButtonOkay->SetAlpha( GetAlpha() );
	m_pButtonOkay->SetCallbackContainer( this );
}

CSDLStateMessageBox::~CSDLStateMessageBox()
{
	DebugInfo( TypeDelete, "Deleting message box." );

	if ( m_pButtonOkay != 0 )
		delete m_pButtonOkay;
	m_pButtonOkay = 0;

	if ( m_pMessage != 0 )
		delete m_pMessage;
	m_pMessage = 0;

	if ( m_pTitle != 0 )
		delete m_pTitle;
	m_pTitle = 0;

	if ( m_sOnExitScript.length() > 0 ) {
		pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnExitScript );
	}
}

void CSDLStateMessageBox::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseMoved( iButton, iX, iY );
}

void CSDLStateMessageBox::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonOkay->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateMessageBox::Render(SDL_Surface* pDestSurface )
{
	//CSDLBaseState::Render( pDestSurface );
	m_pBackground->Render( pDestSurface );
	
	m_pMessage->Render( pDestSurface );
	m_pTitle->Render( pDestSurface );
	m_pButtonOkay->Render( pDestSurface );
}

void CSDLStateMessageBox::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( pObject == m_pButtonOkay ) {
		pEngine->GetStateHandler()->DelayedPopLayer();
	}
}