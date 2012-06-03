
#include "SDLStateGameList.h"
#include "SDLStateLoadingGame.h"
#include "EngineMain.h"

//#include "SDLMultilineTextObject.h"

CSDLStateGameList::CSDLStateGameList()
{
	DebugInfo( TypeCreate, "Creating game list state." );

	m_iPosX = 100;
	m_iPosY = 200;

	pEngine->SetInGame( false );

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( g_sAppDir + "\\Media\\WikiAdventure\\Games.jpg" );

	SDL_Color stBlueish = { 100, 100, 255 };
	m_pDescription = new CSDLCenterTextObject( "Default", "Please select a game from the list.", stBlueish );
	m_pDescription->SetPos( 400, 540 );

	m_pGameList = new CSDLTextSelectionList;
	m_pGameList->SetPos( m_iPosX, m_iPosY );
	m_pGameList->SetCallbackContainer( this );
}

CSDLStateGameList::~CSDLStateGameList()
{
	DebugInfo( TypeDelete, "Deleting game list state." );

	if ( m_pGameList != 0 )
		delete m_pGameList;
	m_pGameList = 0;
}

void CSDLStateGameList::LoadGameList( const string& sGameListURL )
{
	//m_pGameHandler = new CGameHandler;
	m_pGameList->Clear();

	pEngine->GetGameHandler()->LoadGameList( sGameListURL );

	for ( unsigned int i = 0; i < pEngine->GetGameHandler()->GetGameCount(); ++i )
	{
		CGameHandler::stGameObjectInfo* stGameInfo = pEngine->GetGameHandler()->GetGameInfo( i );
		AddGame( stGameInfo->sName );
	}
}

void CSDLStateGameList::AddGame( const string& sGameName )
{
	m_pGameList->AddObject( new CSDLBaseTextObject( "DefaultLarge", sGameName ) );
}

void CSDLStateGameList::Think( const int& iElapsedTime )
{
	CSDLBaseState::Think( iElapsedTime );

	m_pGameList->Think( iElapsedTime );
}

void CSDLStateGameList::Render( SDL_Surface *pDestSurface ) 
{
	CSDLBaseState::Render( pDestSurface );

	m_pGameList->Render( pDestSurface );
}

void CSDLStateGameList::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pGameList->MouseMoved( iButton, iX, iY );
}

void CSDLStateGameList::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	if ( m_pGameList != 0 )
		m_pGameList->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateGameList::OnEnter( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnEnter( pObject );

	// Hack. Loops through the list to find the index of the item entered.
	for ( unsigned int i = 0; i < m_pGameList->GetCount(); ++i )
	{
		if ( pObject == m_pGameList->GetObjectByIndex( i ) )
		{
			// Item number 'i' got focus.
			try	{
				CSDLBaseTextObject* pHover = static_cast<CSDLBaseTextObject*>( pObject );
				if ( pHover->GetFocus() )
					m_pDescription->SetText( pEngine->GetGameHandler()->GetGameInfo( i )->sDescription );
			} catch ( ... ) { 
				// Object is not a text object, just ignore it.	
				m_pDescription->SetText( "Not a valid object." );
			}

			return;
		}
	}
}

void CSDLStateGameList::OnLeave( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnLeave( pObject );
	if ( m_iObjectsWithFocus == 0 )
		m_pDescription->SetText( "" );
}

void CSDLStateGameList::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	// Hack. Loops through the list to find the index of the item entered.
	for ( unsigned int i = 0; i < m_pGameList->GetCount(); ++i )
	{
		if ( pObject == m_pGameList->GetObjectByIndex( i ) )
		{
			// Item number 'i' got focus.
			try	{
				CSDLBaseTextObject* pHover = static_cast<CSDLBaseTextObject*>( pObject );
				if ( pHover->GetFocus() )
				{
					m_pDescription->SetText( "Loading Game '" + pHover->GetText() + "'" );

					//string sName = pEngine->GetGameHandler()->GetGameInfo( i )->sName;
					string sPage = pEngine->GetGameHandler()->GetGameInfo( i )->sPage;
					//pEngine->SetGameName( sName );

					pEngine->GetStateHandler()->NewLayerDelayedClear( new CSDLStateLoadingGame( sPage ) );
				}
			} catch ( ... ) { 
				// Object is not a text object, just ignore it.	
				m_pDescription->SetText( "Not a valid object." );
			}

			return;
		}
	}
}