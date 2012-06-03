
#include "SDLDialogList.h"
#include "SDLDebugTextObject.h"

#include "EngineMain.h"

#include "SDLMultilineTextObject.h"

CSDLDialogList::CSDLDialogList()
{
	m_pMainDialog = 0;
	//m_pCurrentDialog = 0;

	m_bNoOptions = false;

	DebugInfo( TypeCreate, "Creating dialog list." );

	SetCallbackContainer( this );
	SetPos( 20, 400 );
}

CSDLDialogList::~CSDLDialogList()
{
	DebugInfo( TypeDelete, "Deleting dialog list." );
}

void CSDLDialogList::Load( CDialogObject* pDialog )
{
	m_pMainDialog = pDialog;

	pEngine->SetCurrentDialogList( this );

	NewDialog( pDialog );
}

void CSDLDialogList::NewDialog( CDialogObject* pDialog )
{
	this->Clear();

	SDL_Color stWhite  = { 255, 255, 255 };
	SDL_Color stBlack  = { 0,     0,   0 };
	SDL_Color stRedish = { 255, 100, 100 };
	SDL_Color stBlueish = { 100, 100, 255 };
	int iMaxWidth = 800 - (GetPosX() * 2);

	CSDLGameDialogObject* pHeader = new CSDLGameDialogObject( pDialog, "DialogNPC", true, iMaxWidth );
	pHeader->LoadDialog();
	AddHeader( pHeader );

	int iDialogIndex = 0;

	vector<CDialogObject*>* pvDialogList = pDialog->GetChildren();

	// If there is no answers available
	if ( pvDialogList->size() > 0 )
	{
		m_bNoOptions = false;
		CSDLGameDialogObject* pPlayerReply = 0;
		for ( unsigned int i = 0; i < pvDialogList->size(); ++i )
		{
			pPlayerReply = new CSDLGameDialogObject( pvDialogList->at( i ), "Dialog", false, iMaxWidth );
			pPlayerReply->LoadDialog();
			if ( pPlayerReply->GetVisible() == true ) {
				++iDialogIndex;
				char czIndex[8];
				sprintf( czIndex, "%d. ", iDialogIndex );
				pPlayerReply->SetText( string(czIndex) + pvDialogList->at( i )->GetDialogText() );

				AddObject( pPlayerReply );
			}
		}
	} else {
		AddObject( new CSDLDebugTextObject( "Dialog", "1. [You've got nothing to say to that...]", stWhite, stBlack, stRedish ) );
		m_bNoOptions = true;
	}

	SetPos( 30, 600 - GetHeight() - 30 );
}

void CSDLDialogList::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	if ( m_bNoOptions == true ) {
		NewDialog( m_pMainDialog );
		return;
	}

	CSDLGameDialogObject* pSelectedDialog = 0;

	try	{
		pSelectedDialog = static_cast<CSDLGameDialogObject*>( pObject );
	} catch ( ... ) { 
		// Object is not a text object, just ignore it.	
		int x = 5;

		// Jump back to the main dialog branch
		NewDialog( m_pMainDialog );
		return;
	}

	// If there is no NPC reply
	if ( pSelectedDialog->GetDialogObject()->GetChildren()->size() == 0 ) 
	{
		// If there is no reply, and the selected dialog is top-level then exit the dialog
		if ( pSelectedDialog->GetDialogObject()->GetParent() == m_pMainDialog ) {
			pEngine->GetStateHandler()->DelayedPopLayer( this );
		} else {
			// Jump back to the main dialog branch
			NewDialog( m_pMainDialog );
		}
	} 
	// If there is a NPC reply
	else 
	{
		CDialogObject* pNPCReply = pSelectedDialog->GetDialogObject()->GetChildren()->at( 0 );
		NewDialog( pNPCReply );
	}
}