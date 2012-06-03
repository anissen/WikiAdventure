
#include "SDLStateQuestionBox.h"
#include "EngineMain.h"

CSDLStateQuestionBox::CSDLStateQuestionBox( const string& sTitle, const string& sMessage )
{
	InitMsgBox( sTitle, sMessage );
}

CSDLStateQuestionBox::CSDLStateQuestionBox( const string& sTitle, const string& sMessage, const string& sOnYesScript )
{
	m_sOnYesScript = sOnYesScript;
	InitMsgBox( sTitle, sMessage );
}

CSDLStateQuestionBox::CSDLStateQuestionBox( const string& sTitle, const string& sMessage, const string& sOnYesScript, const string& sOnNoScript )
{
	m_sOnYesScript = sOnYesScript;
	m_sOnNoScript  = sOnNoScript;
	InitMsgBox( sTitle, sMessage );
}

void CSDLStateQuestionBox::InitMsgBox( const string& sTitle, const string& sMessage )
{
	DebugInfo( TypeCreate, "Creating question box." );

	m_iSelected = 0;

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

	m_pButtonYes = new CSDLBaseTextObject( "GameDefault", "Yes", stBlueish );
	m_pButtonYes->SetPos( GetPosX() + 30 , (m_iPosY + iHeight) - m_pButtonYes->GetHeight() - 9 );
	m_pButtonYes->SetAlpha( GetAlpha() );
	m_pButtonYes->SetCallbackContainer( this );

	m_pButtonNo = new CSDLBaseTextObject( "GameDefault", "No", stBlueish );
	m_pButtonNo->SetPos( GetPosX() + iWidth - m_pButtonNo->GetWidth() - 30 , (m_iPosY + iHeight) - m_pButtonNo->GetHeight() - 9 );
	m_pButtonNo->SetAlpha( GetAlpha() );
	m_pButtonNo->SetCallbackContainer( this );
}

CSDLStateQuestionBox::~CSDLStateQuestionBox()
{
	DebugInfo( TypeDelete, "Deleting question box." );

	if ( m_pButtonNo != 0 )
		delete m_pButtonNo;
	m_pButtonNo = 0;

	if ( m_pButtonYes != 0 )
		delete m_pButtonYes;
	m_pButtonYes = 0;

	if ( m_pMessage != 0 )
		delete m_pMessage;
	m_pMessage = 0;

	if ( m_pTitle != 0 )
		delete m_pTitle;
	m_pTitle = 0;

	if ( m_iSelected == 1 && m_sOnYesScript.length() > 0 ) {
		pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnYesScript );
	} 
	else if ( m_iSelected == 2 && m_sOnNoScript.length() > 0 ) {
		pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnNoScript );
	}
}

void CSDLStateQuestionBox::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonYes->MouseMoved( iButton, iX, iY );
	m_pButtonNo->MouseMoved( iButton, iX, iY );
}

void CSDLStateQuestionBox::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	m_pButtonYes->MouseButtonDown( iButton, iX, iY );
	m_pButtonNo->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateQuestionBox::Render(SDL_Surface* pDestSurface )
{
	m_pBackground->Render( pDestSurface );
	
	m_pMessage->Render( pDestSurface );
	m_pTitle->Render( pDestSurface );
	m_pButtonNo->Render( pDestSurface );
	m_pButtonYes->Render( pDestSurface );
}

void CSDLStateQuestionBox::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( pObject == m_pButtonYes ) {
		m_iSelected = 1;
		pEngine->GetStateHandler()->DelayedPopLayer();
	} else if ( pObject == m_pButtonNo ) {
		m_iSelected = 2;
		pEngine->GetStateHandler()->DelayedPopLayer();
	}
}