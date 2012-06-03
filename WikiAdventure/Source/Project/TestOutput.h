
#ifndef TESTOUTPUT_H
#define TESTOUTPUT_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "DialogObject.h"
#include "LuaScriptHandler.h"

CLuaScriptHandler LuaScript;

CDialogObject* GetRootDialog( CDialogObject* pDialog )
{
	CDialogObject* pTemp = pDialog;
	while ( pTemp->GetParent()->GetParent() != 0 )
		pTemp = pTemp->GetParent();

	return pTemp;
}

int HandleInput( int iMin, int iMax )
{
	int iSelection = 0;
	while( true )
	{
		cout << endl << "Make your choice: ";
		cin  >> iSelection;
		cout << endl;

		// If the selection is valid (within the boundaries of the answers)
		if ( (iSelection >= iMin) && ( iSelection <= iMax ) )
			break;

		cout << "Invalid selection. Please choose a value between " << iMin << " and " << iMax << "." << endl;
	}
	return iSelection;
}

void PrintReplies( vector<CDialogObject*>* vReplies )
{
	// Loop through all the possible answers for the dialog and print them
	for ( unsigned int i = 0; i < vReplies->size(); ++i )
	{
		cout << "  #" << i + 1 << ": " << vReplies->at(i)->m_sDialogText << endl;
	}
}

void DoHandleDialog ( CDialogObject* pDialog )
{
	// TODO: This is a terrible hack - FIX IT!!
	cout << GetRootDialog( pDialog )->GetParent()->m_sSpeakerID << ": " << pDialog->m_sDialogText << endl;
	/*
	if ( pDialog->GetEventOnAfter().length() > 0 )
	{
		LuaScript.DoLuaScript( pDialog->GetEventOnAfter() );
	}
	*/

	// If there is no answers available
	if ( pDialog->m_vpDialogs.size() == 0 )
	{
		cout << endl << "You've got nothing to say to that..." << endl;
		cout << "[ Back ]" << endl << endl;

		DoHandleDialog( GetRootDialog( pDialog ) );
		return;
	}

	vector<CDialogObject*>* vReplies = &pDialog->m_vpDialogs;

	PrintReplies( vReplies );
	int iSelection = HandleInput( 0, vReplies->size() );

	// Zero is the abort-button
	if (iSelection == 0)
	{
		cout << "Exit was chosen. Bye!" << endl;
		return;
	}

	CDialogObject* pNewDialog = vReplies->at( iSelection - 1 );
	if ( pNewDialog->m_vpDialogs.size() == 0 )
	{
		cout << "The chosen dialog item has no sub-items! Sue the dialog writer!" << endl;
		cout << "[ Back ]" << endl << endl;
		DoHandleDialog( GetRootDialog( pNewDialog ) );
	}

	DoHandleDialog( pNewDialog->m_vpDialogs[0] );
}

#endif // TESTOUTPUT_H