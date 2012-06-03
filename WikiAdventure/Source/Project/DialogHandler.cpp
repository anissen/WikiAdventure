
#include "DialogHandler.h"

CDialogHandler::CDialogHandler()
{
	m_pDialogList		= 0;
	m_pDialogLoading	= 0;
}

CDialogHandler::~CDialogHandler()
{
	map<string, CDialogObject*>::iterator DialogIter = m_mpDialogs.begin();
	while ( DialogIter != m_mpDialogs.end() )
	{
		if ( DialogIter->second != 0 )
		{
			DebugInfo( TypeDelete, string("Deleting dialog with ID \"" + DialogIter->first + "\".").c_str() );
			delete DialogIter->second;
		}

		++DialogIter;
	}
}

void CDialogHandler::LoadContents( const string& sRawDialogBlock )
{
	m_pDialogList	= new CWikiContent( sRawDialogBlock, "Dialog" );
}

CDialogObject* CDialogHandler::GetDialog( const string& sDialogID )
{
	if ( m_mpDialogs.count( sDialogID ) == 0 ) {
		//DebugInfo( TypeError, "Dialog with ID \"" + sDialogID + "\" not found!" );
		return 0;
	}
		
	return m_mpDialogs[ sDialogID ];
}

stLoadStatus CDialogHandler::LoadNext()
{
	stLoadStatus stReturn;

	stReturn.iNumberLoaded	= m_pDialogList->GetCountPopped();
	stReturn.iTotalCount	= m_pDialogList->GetCountLoaded();

	if ( m_pDialogList->GetCountLeft() == 0 )
	{
		stReturn.sStatus = "Finished!";
		stReturn.eObjectLoaded = DialogLoaded;
		m_bLoadFinished = true;
		return stReturn;
	}

	string sDialogID = m_pDialogList->GetParameter( "Dialog ID: ", "[No ID]" );

	if ( m_mpDialogs.count( sDialogID ) )
	{
		DebugInfo( TypeWarning, 
			string("Dialog with ID \"" + sDialogID + "\" already defined!").c_str() );
	}
	else
	{
		// Load the location
		CDialogObject* pDialog = new CDialogObject;
		m_mpDialogs[ sDialogID ] = pDialog;
		pDialog->LoadContents( m_pDialogList->GetTagText() );

		stReturn.sStatus = "Loading dialog \"" + sDialogID + "\"";
		stReturn.eObjectLoaded = DialogLoaded;
	}

	m_pDialogList->Pop();

	return stReturn;
}

/*
:'''<Dialog>'''

[data]

:'''</Dialog>'''
*/