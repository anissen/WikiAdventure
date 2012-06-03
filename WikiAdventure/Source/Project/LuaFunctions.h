
#include "../WA-SDL/Globals.h"
#include "../WA-SDL/EngineMain.h"
#include "../WA-SDL/SDLStateGameMenu.h"

#include "..\\Lua\\LuaPlus.h"
using namespace LuaPlus;

/*
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
*/


/** Example external Lua function.
	@param	State Pointer to a LuaState object.
	@return	The result as an integer.
*/
static int LuaPrint( LuaState* State )
{
	LuaStack args( State );

	pEngine->GetDebugOverlay()->AddInfo( "The following is printed using Lua scripting: " );
	pEngine->GetDebugOverlay()->AddWarning( args[1].GetString() );

	return 1;
}

static int LuaStartDialog( LuaState* State )
{
	LuaStack args( State );

	pEngine->GetCurrentLocation()->StartDialog( args[1].GetString() );

	return 1;
}

static int LuaHideThisItem( LuaState* State )
{
	pEngine->GetCurrentItem()->SetVisible( false );

	return 1;
}

//static int LuaShowThisItem( LuaState* State )
//{
//	pEngine->GetCurrentItem()->SetVisible( true );
//
//	return 1;
//}

static int LuaStartLocation( LuaState* State )
{
	LuaStack args( State );

	string sLocation = args[1].GetString();

	DebugInfo( TypeInfo, string("Loading location \"" + sLocation + "\"").c_str() );

	pEngine->GetLuaScriptHandler()->DoLuaScript( "Location = \"" + sLocation + "\"" );
	pEngine->GetLuaScriptHandler()->DoLuaScript( "SaveGame()" );

	CSDLStateLocation* pLocation = new CSDLStateLocation;
	pEngine->GetStateHandler()->NewLayerDelayedClear( pLocation );
	pLocation->Load( pEngine->GetGameHandler()->GetLoadedGame()->GetLocations()->GetLocation( sLocation ) );

	pEngine->SetInGame( true );
	pEngine->SetCurrentLocationName( sLocation );

	return 1;
}

static int LuaSaveGame( LuaState* State )
{
	pEngine->GetLuaScriptHandler()->DumpToFile( "Media\\" + pEngine->GetGameDir() + "\\SaveGame.was" );
	DebugInfo( TypeInfo, "Game saved" );

	return 1;
}

static int LuaBackToGameMenu( LuaState* State )
{
	pEngine->GetLuaScriptHandler()->DoLuaScript( "SaveGame()" );
	pEngine->GetStateHandler()->NewLayerDelayedClear( new CSDLStateGameMenu );

	return 1;
}

static int LuaHideThisDialog( LuaState* State )
{
	pEngine->GetCurrentDialog()->SetVisible( false );

	return 1;
}

//static int LuaShowThisDialog( LuaState* State )
//{
//	pEngine->GetCurrentDialog()->SetVisible( true );
//
//	return 1;
//}

static int LuaChangeDialogText( LuaState* State )
{
	LuaStack args( State );
	pEngine->GetCurrentDialog()->SetText( args[1].GetString() );

	return 1;
}

static int LuaShowMessageBox( LuaState* State )
{
	LuaStack args( State );

	string sTitle	= args[1].GetString();
	string sText	= ReplaceBR( args[2].GetString() );

	if ( args[3].IsNone() ) {
		pEngine->GetStateHandler()->PushLayer( new CSDLStateMessageBox( sTitle, sText ) );
	} else {
		string sOnExitScript = ReplaceBR( args[3].GetString() );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateMessageBox( sTitle, sText, sOnExitScript ) );
	}

	return 1;
}

static int LuaShowQuestionBox( LuaState* State )
{
	LuaStack args( State );

	string sTitle	= args[1].GetString();
	string sText	= ReplaceBR( args[2].GetString() );

	if ( args[3].IsNone() ) {
		pEngine->GetStateHandler()->PushLayer( new CSDLStateQuestionBox( sTitle, sText ) );
	} 
	else if ( args[4].IsNone() ) 
	{
		string sOnYesScript = ReplaceBR( args[3].GetString() );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateQuestionBox( sTitle, sText, sOnYesScript ) );
	}
	else if ( args[5].IsNone() )
	{
		string sOnYesScript = ReplaceBR( args[3].GetString() );
		string sOnNoScript  = ReplaceBR( args[4].GetString() );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateQuestionBox( sTitle, sText, sOnYesScript, sOnNoScript ) );
	} else {
		DebugInfo( TypeError, "Wrong number of arguments passed to script" );
	}

	return 1;
}

static int LuaShowPicture( LuaState* State )
{
	LuaStack args( State );

	string sPicture = args[1].GetString();

	if ( args[2].IsNone() ) {
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowPicture( sPicture ) );
	} else {
		string sOnExitScript = ReplaceBR( args[2].GetString() );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowPicture( sPicture, sOnExitScript) );
	}

	return 1;
}

/*
static void LuaShowText( const char* sText = "Hello World", const char* sOnExitScript = "" )
{
	//string sText = ReplaceInText( args[1].GetString(), "<br>", "\n" );

	if ( string(sOnExitScript).length() == 0 ) {
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowText( sText ) );
	} else {
		//string sOnExitScript = ReplaceInText( args[2].GetString(), "<br>", "\n" );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowText( sText, sOnExitScript ) );
	}
}
*/

static int LuaShowText( LuaState* State )
{
	LuaStack args( State );

	string sText = ReplaceBR( args[1].GetString() );

	if ( args[2].IsNone() ) {
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowText( sText ) );
	} else {
		string sOnExitScript = ReplaceBR( args[2].GetString() );
		pEngine->GetStateHandler()->PushLayer( new CSDLStateShowText( sText, sOnExitScript ) );
	}

	return 1;
}

static int LuaEndDialog( LuaState* State )
{
	if ( pEngine->GetCurrentDialogList() != 0 ) {
		pEngine->GetStateHandler()->DelayedPopLayer( pEngine->GetCurrentDialogList() );
	}

	return 1;
}

static int LuaEndDialogThread( LuaState* State )
{
	if ( pEngine->GetCurrentDialogList() != 0 ) {
		pEngine->GetCurrentDialogList()->NewDialog( pEngine->GetCurrentDialogList()->GetMainDialog() );
	}

	return 1;
}
