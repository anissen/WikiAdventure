
#include "SDLGameItemObject.h"
#include "EngineMain.h"

CSDLGameItemObject::CSDLGameItemObject()
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_sDescription = "[None]";

	/*

	*/
	
}

CSDLGameItemObject::~CSDLGameItemObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );

	// Run OnAfter-script at shutdown
}

void CSDLGameItemObject::LoadItem()
{
	// Run OnLoad-script at startup
	if ( m_sOnLoad.length() > 0 ) {
		pEngine->SetCurrentItem( this );
		DebugInfo( TypeInfo, "Executing OnLoad Lua script." );
		CLuaScriptHandler::ScriptResults iResult = pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnLoad );
		DebugInfo( TypeInfo, pEngine->GetLuaScriptHandler()->GetResult( iResult ).c_str() );
	}
}

void CSDLGameItemObject::OnMouseClicked( const int& iButton )
{
	// Run OnClick-script
	if ( m_sOnClick.length() > 0 ) {
		pEngine->SetCurrentItem( this );
		DebugInfo( TypeInfo, "Executing OnClick Lua script." );
		CLuaScriptHandler::ScriptResults iResult = pEngine->GetLuaScriptHandler()->DoLuaScript( m_sOnClick );
		DebugInfo( TypeInfo, pEngine->GetLuaScriptHandler()->GetResult( iResult ).c_str() );
	}
}