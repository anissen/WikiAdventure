
#include "LuaScriptHandler.h"
#include "LuaFunctions.h"

CLuaScriptHandler::CLuaScriptHandler()
{
	//Create state
	//LuaStateOwner State;

	//LuaState* state = LuaState::Create();

	//With this the script can access our own C++ functions:
	// State->GetGlobals().Register("GiveItem", GiveItem);
	
	m_oLuaState->GetGlobals().Register( "Print",			LuaPrint );
	m_oLuaState->GetGlobals().Register( "StartDialog",		LuaStartDialog );
	m_oLuaState->GetGlobals().Register( "HideThisItem",		LuaHideThisItem );
	//m_oLuaState->GetGlobals().Register( "ShowThisItem",		LuaShowThisItem );
	m_oLuaState->GetGlobals().Register( "StartLocation",	LuaStartLocation );
	m_oLuaState->GetGlobals().Register( "HideThisDialog",	LuaHideThisDialog );
	//m_oLuaState->GetGlobals().Register( "ShowThisDialog",	LuaShowThisDialog );
	m_oLuaState->GetGlobals().Register( "ChangeDialogText",	LuaChangeDialogText );
	m_oLuaState->GetGlobals().Register( "ShowMessage",		LuaShowMessageBox );
	m_oLuaState->GetGlobals().Register( "ShowPicture",		LuaShowPicture );
	m_oLuaState->GetGlobals().Register( "ShowText",			LuaShowText );
	m_oLuaState->GetGlobals().Register( "ShowQuestion",		LuaShowQuestionBox );
	m_oLuaState->GetGlobals().Register( "SaveGame",			LuaSaveGame );
	m_oLuaState->GetGlobals().Register( "BackToGameMenu",	LuaBackToGameMenu );
	m_oLuaState->GetGlobals().Register( "EndDialog",		LuaEndDialog );
	m_oLuaState->GetGlobals().Register( "EndDialogThread",	LuaEndDialogThread );
	

	//m_oLuaState->GetGlobals().RegisterDirect( "ShowText", LuaShowText );

    //DoLuaFile( "dump.txt" );
}

CLuaScriptHandler::~CLuaScriptHandler()
{
	//LuaState::Destroy(state);
	//m_oLuaState->DumpGlobals( "dump.txt" );
}

CLuaScriptHandler::ScriptResults CLuaScriptHandler::DoLuaScript( const string& sScript )
{
	DebugInfo( TypeInfo, "Executing Lua script string." );

	int iResult = m_oLuaState->DoString( sScript.c_str() );
	ScriptResults eReturn;

	switch ( iResult ) 	{
		case 0:						eReturn = eSuccess;	break;
		case LuaState::ERRRUN:		eReturn = eSuccess;	break;
		case LuaState::ERRFILE:		eReturn = eFileError;	break;
		case LuaState::ERRSYNTAX:	eReturn = eSyntaxError;	break;
		case LuaState::ERRMEM:		eReturn = eMemoryError;	break;
		default:					eReturn = eError;	break;	// Unknown
	}

	DebugInfo( TypeInfo, string("Finished executing Lua script with result: " + GetResult( eReturn )).c_str() );
	return eReturn;
}

CLuaScriptHandler::ScriptResults CLuaScriptHandler::DoLuaFile( const string& sFile )
{
	DebugInfo( TypeInfo, "Executing Lua script file." );

	int iResult = m_oLuaState->DoFile( sFile.c_str() );
	ScriptResults eReturn;

	switch ( iResult ) 	{
		case 0:						eReturn = eSuccess;	break;
		case LuaState::ERRRUN:		eReturn = eSuccess;	break;
		case LuaState::ERRFILE:		eReturn = eFileError;	break;
		case LuaState::ERRSYNTAX:	eReturn = eSyntaxError;	break;
		case LuaState::ERRMEM:		eReturn = eMemoryError;	break;
		default:					eReturn = eError;	break;	// Unknown
	}

	DebugInfo( TypeInfo, string("Finished executing Lua script file with result: " + GetResult( eReturn )).c_str() );
	return eReturn;
}

string CLuaScriptHandler::GetResult( ScriptResults eResult )
{
	string sResult;

	switch ( eResult ) 	{
		case eSuccess:		sResult = "Success";		break;
		case eFileError:	sResult = "File Error";		break;
		case eSyntaxError:	sResult = "Syntax Error";	break;
		case eMemoryError:	sResult = "Memory Error";	break;	
		default:			sResult = "Unknown Error";	break;
	}

	return sResult;
}

void CLuaScriptHandler::DumpToFile( const string& sFile )
{
	bool bResults = m_oLuaState->DumpGlobals( sFile.c_str() );
}