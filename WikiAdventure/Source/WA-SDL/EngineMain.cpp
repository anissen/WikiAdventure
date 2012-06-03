
#include "EngineMain.h"

string g_sAppDir;

void WriteDebugData( const eDebugType eType, const char* czFile, const char* czFunction, const long lLine, const char* czText )
{
	//fprintf( stdout, "\n[%s] \t %s (%s line %d) \n %s \n\n", czType, czFunction, czFile, lLine, czText );
	//fprintf( stdout, "\n[%d] \t %s \n \t %s", eType, czFunction, czText );
	
	if ( pEngine != 0 && pEngine->GetDebugOverlay() != 0 )
	{
		string sText = czText; //string(czFunction) + ": " + string(czText);

		switch ( eType ) 
		{
		case TypeCreate:	
			{
				SDL_Color SGreenish = { 100, 255, 100 }; 
				pEngine->GetDebugOverlay()->AddObject( new CSDLDebugTextObject( "Debug", sText, SGreenish ) ); 
				break;
			}
		case TypeDelete:
			{
				SDL_Color SRedish = { 255, 100, 100 }; 
				pEngine->GetDebugOverlay()->AddObject( new CSDLDebugTextObject( "Debug", sText, SRedish ) ); 
				break;
			}
		case TypeInfo:		pEngine->GetDebugOverlay()->AddInfo	 ( sText ); break;
		case TypeWarning:	fprintf( stderr, "\nWARNING: \t %s \n \t %s", czFunction, czText );
							pEngine->GetDebugOverlay()->AddWarning( sText ); 
							break;
		case TypeError:		fprintf( stderr, "\nERROR: \t %s \n \t %s", czFunction, czText );
							pEngine->GetDebugOverlay()->AddError	 ( sText ); 
							break;
		default:			pEngine->GetDebugOverlay()->AddWarning( "[Unspecified Debug Type] " + sText ); break;
		}

	} else {
		fprintf( stderr, "\n[%d] \t %s \n \t %s", eType, czFunction, czText );
	}
}

CMyEngine::CMyEngine()
{
	pStateHandler			= 0;
	bDebugMode				= false;
	pDebugOverlay			= 0;
	pStateHandler			= 0;
	pLuaScriptHandler		= 0;
	m_pCurrentLocation		= 0;
	m_pGameHandler			= 0;
	m_pCurrentItem			= 0;
	m_pCurrentDialog		= 0;
	m_pLocationOverlay		= 0;
	m_bInGame				= false;
	m_pCurrentDialogList	= 0;

	SetTitle("WikiAdventure - Loading Core...");
}

CMyEngine::~CMyEngine()
{
	// Nothing
}

void CMyEngine::AdditionalInit()
{	
	FontHandler.AddFont( g_sAppDir + "\\Media\\WikiAdventure\\Debug.ttf", "Debug", 17 );
	
	pDebugOverlay = new CSDLDebugOverlay;
	m_pGameHandler = new CGameHandler;
	pLuaScriptHandler = new CLuaScriptHandler;

	bDebugMode = false;

	FontHandler.AddFont( g_sAppDir + "\\Media\\WikiAdventure\\Default.ttf", "Default", 22 );
	FontHandler.AddFont( g_sAppDir + "\\Media\\WikiAdventure\\Default.ttf", "DefaultSmall", 20 );
	FontHandler.AddFont( g_sAppDir + "\\Media\\WikiAdventure\\Default.ttf", "DefaultLarge", 24 );
	FontHandler.AddFont( g_sAppDir + "\\Media\\WikiAdventure\\Misc.ttf", "LoadText", 26 );
	
	pStateHandler = new CSDLStateHandler;
	pStateHandler->PushLayer( new CSDLStateLoading );

	SetTitle("WikiAdventure - Download, parsing, initiating...");

	CEngine::DoThink();
	CEngine::DoRender();
}

void CMyEngine::End()
{
	SetTitle("WikiAdventure - Quiting...");

	if ( pStateHandler != 0 )
		delete pStateHandler;
	pStateHandler = 0;

	if ( pLuaScriptHandler != 0 )
		delete pLuaScriptHandler;
	pLuaScriptHandler = 0;

	if ( m_pGameHandler != 0 )
		delete m_pGameHandler;
	m_pGameHandler = 0;

	if ( pDebugOverlay != 0 )
		delete pDebugOverlay;
	pDebugOverlay = 0;
}

void CMyEngine::Think( const int& iElapsedTime )
{
	pStateHandler->Think( iElapsedTime );

	if ( GetInGame() ) {
		if ( m_pLocationOverlay != 0 )
			m_pLocationOverlay->Think( iElapsedTime );
	}

	// Think even if we don't show the data
	pDebugOverlay->Think( iElapsedTime );
}

void CMyEngine::Render( SDL_Surface* pDestSurface )
{
	pStateHandler->Render( pDestSurface );

	if ( GetInGame() ) {
		if ( m_pLocationOverlay != 0 )
			m_pLocationOverlay->Render( pDestSurface );
	}

	if ( bDebugMode )
	{
		pDebugOverlay->SetFPSValue( GetFPS() );
		pDebugOverlay->Render( pDestSurface );
	}
}

void CMyEngine::KeyDown(const int& iKeyEnum)
{    
	if ( iKeyEnum == SDLK_b )
		bDebugMode = !bDebugMode;
}


void CMyEngine::KeyUp(const int& iKeyEnum)
{

}

void CMyEngine::MouseMoved(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{
	pStateHandler->MouseMoved( iButton, iX, iY );

	if ( GetInGame() ) {
		if ( m_pLocationOverlay != 0 )
			m_pLocationOverlay->MouseMoved( iButton, iX, iY );
	}

	if ( bDebugMode )
		pDebugOverlay->MouseMoved( iButton, iX, iY );
}

void CMyEngine::MouseButtonUp(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{
	pStateHandler->MouseButtonUp( iButton, iX, iY );

	if ( GetInGame() ) {
		if ( m_pLocationOverlay != 0 )
			m_pLocationOverlay->MouseButtonUp( iButton, iX, iY );
	}

	if ( bDebugMode )
		pDebugOverlay->MouseButtonUp( iButton, iX, iY );
}

void CMyEngine::MouseButtonDown(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY)
{
	if ( pStateHandler != 0 )
		pStateHandler->MouseButtonDown( iButton, iX, iY );

	if ( GetInGame() ) {
		if ( m_pLocationOverlay != 0 )
			m_pLocationOverlay->MouseButtonDown( iButton, iX, iY );
	}

	if ( bDebugMode )
		pDebugOverlay->MouseButtonDown( iButton, iX, iY );
}
