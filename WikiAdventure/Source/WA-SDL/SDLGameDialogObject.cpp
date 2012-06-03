
#include "SDLGameDialogObject.h"
#include "EngineMain.h"

CSDLGameDialogObject::CSDLGameDialogObject( CDialogObject* pDialog, const string& sFontID, bool bHeader, int iMaximumWidth )
: m_pDialog(pDialog), m_bHeader(bHeader), CSDLMultilineDebugTextObject( 
							   sFontID, 
							   (!bHeader ? pDialog->GetDialogText() : pDialog->GetRootDialog()->GetParent()->GetSpeakerID() + ":\n" + pDialog->GetDialogText()), 
							   (!bHeader ? stWhite : stNPC), 
							   stBlack, 
							   stBlueish, 
							   stBlack,
							   iMaximumWidth
							   )
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );

}

CSDLGameDialogObject::~CSDLGameDialogObject()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );

	// Run OnAfter-script at shutdown
}

void CSDLGameDialogObject::SetText( const string& sText )
{
	string sNewText;
	if ( m_bHeader == true ) {
		sNewText = m_pDialog->GetRootDialog()->GetParent()->GetSpeakerID() + ":\n" + sText;
	} else {
		sNewText = sText;
	}

	CSDLMultilineDebugTextObject::SetText( sNewText );
}

void CSDLGameDialogObject::LoadDialog()
{
	// Run OnLoad-script at startup
	string sOnLoad = m_pDialog->GetOnLoad();
	if ( sOnLoad.length() > 0 ) {
		pEngine->SetCurrentDialog( this );
		CLuaScriptHandler::ScriptResults iResult = pEngine->GetLuaScriptHandler()->DoLuaScript( sOnLoad );
	}
}

void CSDLGameDialogObject::OnMouseClicked( const int& iButton )
{
	// Run OnClick-script
	string sOnClick = m_pDialog->GetOnClick();
	if ( sOnClick.length() > 0 ) {
		pEngine->SetCurrentDialog( this );
		CLuaScriptHandler::ScriptResults iResult = pEngine->GetLuaScriptHandler()->DoLuaScript( sOnClick );
	}
}