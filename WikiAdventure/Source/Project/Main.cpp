
// Include the Doxygen commented file containing the main page
/**	@file MainPage.dox */

#include "Globals.h"
//#include "GameHandler.h"
//#include "DialogHandler.h"
#include "Util.h"

#include "../WA-SDL/EngineMain.h"
#include "../WA-SDL/SDLStateLoadingGame.h"
CMyEngine* pEngine;

#ifdef DEBUG_APP_LOG
	CDebugLogHandler* pDebugLog;
#endif

void LoadGames( const string& sGamePage );

int main( int argc, char* argv[] )
{
	//string sAppDir = GetUntilLast( argv[0], "\\" );

	/* This is a hacky thing to avoid messing with the command line arguments. Remove for normal usage.	*/
	//argc = 2; argv[1] = "wikiadventure://";
	/* End of hack thing. */

	char czFullName[ MAX_PATH + 1 ];
	GetModuleFileName( NULL, czFullName, MAX_PATH );
	
	g_sAppDir = GetUntilLast( czFullName, "\\" );

	DebugInfo( TypeInfo, string("Application directory: " + g_sAppDir).c_str() );

	// Init the debug log, if it is activated
#ifdef DEBUG_APP_LOG
	pDebugLog = new CDebugLogHandler( g_sAppDir +  "\\Log\\Debug.xml" );
	
	pDebugLog->AddTagTree( "Project" );
	pDebugLog->AddTag( "Name", "WikiDialog Reader" );
	pDebugLog->AddTag( "MainSourceDir", GetUntilLast( __FILE__, "\\" ) );
	pDebugLog->AddTag( "Compiled", COMPILE_TIMESTAMP );

	pDebugLog->AddTagTree( "CmdArguments" );
	for ( int i = 0; i < argc; ++i )
        pDebugLog->AddTag( "CmdArgument", argv[i] );
	pDebugLog->CloseTagTree(); // CmdArguments

	pDebugLog->AddTagTree( "LogEntries" );
#endif

	for ( int i = 0; i < argc; ++i )
		DebugInfo( TypeInfo, string("Command line: " + string(argv[i])).c_str() );

	if ( argc != 2 ) {
		DebugInfo( TypeWarning, "Application is called with an invalid number of arguments." );
		argc = 2; argv[1] = "";
	}

	string sGamePage = GetAfterLast( argv[1], "//" );
	// Remove "/" from text and replace "_" with a space
	sGamePage = ReplaceInText( RemoveFromText( sGamePage, "/" ), "_", " " );

	DebugInfo(TypeInfo, string("Game page: " + sGamePage).c_str() );

	pEngine = new CMyEngine;
	
	LoadGames( sGamePage );

	// Terminate the debug log, if is it activated
#ifdef DEBUG_APP_LOG
	if ( pDebugLog != 0 )
		delete pDebugLog;
#endif

	return 0;
}

void LoadGames( const string& sGamePage )
{
	string sFinalURL = sMainURL + sMainPage;
	
	if ( sGamePage.length() != 0 )
	{
		sFinalURL += ":" + sGamePage;
	}
	sFinalURL += "&action=raw";

	pEngine->SetTitle("WikiAdventure - Loading...");
	pEngine->Init();
	pEngine->SetTitle("WikiAdventure");

	bool m_bUrlUnreachable = true;
	if ( InternetCheckConnection( sFinalURL.c_str(), FLAG_ICC_FORCE_CONNECTION, 0 ) == 0 )
	{
		m_bUrlUnreachable = false;

		string sMessage = "The specified website (\"" + sFinalURL + "\") cannot be reached.\nReason: No internet connection or invalid website URL.\n\n WikiAdventure is quiting... sorry :(";
		MessageBox( 0, sMessage.c_str(), "Website is unreachable", 0 );
	}
	else
	{
		if ( sGamePage.length() == 0 ) 
		{
			CSDLStateGameList* pGameList = new CSDLStateGameList;
			pEngine->GetStateHandler()->NewLayer( pGameList );
			pGameList->LoadGameList( sFinalURL );
		} 
		else
		{
			pEngine->GetStateHandler()->NewLayer( new CSDLStateLoadingGame( sGamePage ) );
		}

		pEngine->Start();
	}

	if ( pEngine != 0 )
		delete pEngine;
	pEngine = 0;
}

