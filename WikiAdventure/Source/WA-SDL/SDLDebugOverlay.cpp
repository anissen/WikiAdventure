
#include "SDLDebugOverlay.h"
#include "EngineMain.h"
#include <time.h>
#include <shellapi.h>

CSDLDebugOverlay::CSDLDebugOverlay()
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_bHighlightRects = false;
	
	m_pFPSCounter = new CSDLBaseTextObject( "Debug", "Current frame rate is [x] frames per second." );
	m_pFPSCounter->SetPos( 5, 5 );

	m_pDebugList = new CSDLDebugQueueList;
	m_pDebugList->SetPosX( 5 );
	m_pDebugList->SetPosY(  m_pFPSCounter->GetButtom() + 5 );

	m_pDebugOptions = new CSDLTextSelectionList;
	m_pDebugOptions->SetPos( 650, 5 );
	m_pDebugOptions->SetCallbackContainer( this );

	m_pDebugOptions->AddHeader( new CSDLBaseTextObject( "Debug", "Debug Options:" ) );
	m_pDebugOptions->AddObject( m_pTextReportBug		= new CSDLBaseTextObject( "Debug", "- Report a bug.",		stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextRequestFeature	= new CSDLBaseTextObject( "Debug", "- Request a feature.",	stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextEditGame			= new CSDLBaseTextObject( "Debug", "- Edit game.",			stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextEditLocation		= new CSDLBaseTextObject( "Debug", "- Edit this location.",	stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pToggleHighlight		= new CSDLBaseTextObject( "Debug", "- Toggle highlighs.",stWarningBG, stWarning ) );
	//m_pDebugOptions->AddObject( new CSDLBaseTextObject( "Debug", "- Log to XML file.",		stWarningBG, stWarning ) );
	//m_pDebugOptions->AddObject( new CSDLBaseTextObject( "Debug", "- Log to text file.",		stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextClearLog			= new CSDLBaseTextObject( "Debug", "- Clear debug list.",	stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextHideDebug		= new CSDLBaseTextObject( "Debug", "- Hide debug screen.",	stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextSaveGame			= new CSDLBaseTextObject( "Debug", "- Save game.",			stWarningBG, stWarning ) );
	m_pDebugOptions->AddObject( m_pTextBackToMenu		= new CSDLBaseTextObject( "Debug", "- Back to game menu.",	stWarningBG, stWarning ) );
	m_pDebugOptions->SetPosX( 800 - m_pDebugOptions->GetWidth() );
}

CSDLDebugOverlay::~CSDLDebugOverlay()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );

	if ( m_pDebugOptions != 0 )
		delete m_pDebugOptions;
	m_pDebugOptions = 0;

	if ( m_pDebugList != 0 )
		delete m_pDebugList;
	m_pDebugList = 0;

	if ( m_pFPSCounter != 0 )
		delete m_pFPSCounter;
	m_pFPSCounter = 0;
}

void CSDLDebugOverlay::SetFPSValue( int iValue )
{
	char czFPSText[64];
	sprintf( czFPSText, "Current frame rate is %d frames per second.", iValue );
	m_pFPSCounter->SetText( czFPSText );
}

void CSDLDebugOverlay::AddObject( CSDLBaseObject* pBaseObject )
{	

	try {
		CSDLBaseTextObject* pTempText = static_cast< CSDLBaseTextObject* >( pBaseObject );

		char timeStr[9];
		_strtime( timeStr );

		pTempText->SetText( timeStr + string(" ") + pTempText->GetText() );
	}
	catch ( ... ) {
		// It isn't a CSDLBaseTextObject* object, so do nothing
	}
	m_pDebugList->AddObject( pBaseObject );
}

void CSDLDebugOverlay::AddInfo( const string& sText )
{
	AddObject( new CSDLDebugTextObject( "Debug", sText, stInfo, stInfoBG  ) );
}

void CSDLDebugOverlay::AddWarning( const string& sText )
{
	AddObject( new CSDLDebugTextObject( "Debug", sText, stWarning, stWarningBG  ) );
}

void CSDLDebugOverlay::AddError( const string& sText )
{
	AddObject( new CSDLDebugTextObject( "Debug", sText, stError, stErrorBG  ) );
}

void CSDLDebugOverlay::Render( SDL_Surface* pDestSurface )
{
	m_pFPSCounter->Render( pDestSurface );

	m_pDebugList->Render( pDestSurface );

	m_pDebugOptions->Render( pDestSurface );
}

void CSDLDebugOverlay::Think( const int& iElapsedTime )
{
	m_pDebugList->Think( iElapsedTime );
}

void CSDLDebugOverlay::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pDebugOptions->MouseMoved( iButton, iX, iY );
}

void CSDLDebugOverlay::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	m_pDebugOptions->MouseButtonDown( iButton, iX, iY );
}

void CSDLDebugOverlay::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( pObject == m_pTextReportBug ) {
		AddError( "[Debug - Report bug]"); 
	HINSTANCE r = ShellExecute(NULL, "open", "http://gpwiki.org/index.php/Community_Projects:WikiAdventure:Bug_Reports&action=edit&section=new", NULL, NULL, SW_SHOWNORMAL);
	} else if ( pObject == m_pTextRequestFeature ) {
		AddError( "[Debug - Request feature]"); 
		HINSTANCE r = ShellExecute(NULL, "open", "http://gpwiki.org/index.php/Community_Projects:WikiAdventure:Feature_Requests&action=edit&section=new", NULL, NULL, SW_SHOWNORMAL);
	} else if ( pObject == m_pTextEditGame) {
		AddError( "[Debug - Edit game]"); 
		string sUrl = "http://www.gpwiki.org/index.php/Community_Projects:WikiAdventure:Games:" + pEngine->GetGameDir();
		HINSTANCE r = ShellExecute(NULL, "open", sUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
	} else if ( pObject == m_pTextEditLocation ) {
		AddError( "[Debug - Edit location]");
		string sUrl = "http://www.gpwiki.org/index.php/Community_Projects:WikiAdventure:Games:" + pEngine->GetGameDir() + ":" + pEngine->GetCurrentLocationName();
		HINSTANCE r = ShellExecute(NULL, "open", sUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
	} else if ( pObject == m_pTextClearLog ) {
		m_pDebugList->Clear();
		AddInfo( "[Debug - Clear log]" );
	} else if ( pObject == m_pToggleHighlight ) {
		AddInfo( "[Debug - Toggle Highligths]" );
		m_bHighlightRects = !m_bHighlightRects;
	} else if ( pObject == m_pTextHideDebug ) {
		AddInfo( "[Debug - Hide debug screen]" );
		pEngine->bDebugMode = false;
	} else if ( pObject == m_pTextSaveGame ) {
		AddInfo( "[Debug - Save game]" );
		pEngine->GetLuaScriptHandler()->DoLuaScript( "SaveGame()" );
	} else if ( pObject == m_pTextBackToMenu ) {
		AddInfo( "[Debug - Back to main]" );
		pEngine->GetLuaScriptHandler()->DoLuaScript( "BackToGameMenu()" );
	} else {
		AddWarning( "[Debug - Action not handled!]" );
	}
}