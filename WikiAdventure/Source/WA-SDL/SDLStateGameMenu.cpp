
#include "SDLStateGameMenu.h"
#include "EngineMain.h"

#include "../Project/Util.h"
#include "../Project/Globals.h"

CSDLStateGameMenu::CSDLStateGameMenu()
{
	DebugInfo( TypeCreate, "Creating game menu." );

	m_iPosX = 400;
	m_iPosY = 120;

	pEngine->SetInGame( false );

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "Menu.jpg" ) );

	SDL_Color stBlueish = { 100, 100, 255 };
	m_pDescription = new CSDLCenterTextObject( "GameDefault", "Please select a option from the list.", stBlueish );
	m_pDescription->SetPos( 400, 540 );

	m_pMenuList = new CSDLTextSelectionList;
	m_pMenuList->SetPos( m_iPosX, m_iPosY );
	m_pMenuList->SetCallbackContainer( this );

	m_pMenuList->SetPos( m_iPosX, m_iPosY );

	SDL_Color stGrey = { 128, 128, 128 };

	if ( DoesMediaExist( pEngine->GetGameDir() + "\\SaveGame.was" ) ) {
		m_bHasSaveGame = true;
		m_pContinueGame = new CSDLCenterTextObject( "GameDefaultLarge", "Continue Game" );
	} else {
		m_bHasSaveGame = false;
		m_pContinueGame = new CSDLCenterTextObject( "GameDefaultLarge", "Continue Game", stGrey, stGrey );
	}
	m_pMenuList->AddObject( m_pContinueGame );

	m_pMenuList->AddObject( m_pStartNewGame =  new CSDLCenterTextObject( "GameDefaultLarge", "Start New Game" ) );

	AddSeparator( 30 );

	m_pMenuList->AddObject( m_pAgeRating = new CSDLCenterTextObject( "GameDefaultLarge", "Age Rating:" ) );

	CSDLMultilineCenterTextObject* pAgeRating = new CSDLMultilineCenterTextObject( string("Dialog"), "", stDefColor, stDefColor ) ;
	string sAgeRating = pEngine->GetGameHandler()->GetLoadedGame()->GetAgeRating();
	if ( sAgeRating.length() == 0 )
		sAgeRating = "[Not specified]";

	pAgeRating->SetText( sAgeRating );
	
	//pAgeRating->SetText( "Rated Moderate (16+)\nStrong language, criminal activities." );

	m_pMenuList->AddObject( pAgeRating );

	AddSeparator( 30 );

	m_pMenuList->AddObject( m_pAuthors = new CSDLCenterTextObject( "GameDefaultLarge", "Author(s):" ) );

	CSDLMultilineCenterTextObject* pAuthors = new CSDLMultilineCenterTextObject( string("Dialog"), "", stDefColor, stDefColor  ) ;
	string sAuthors = pEngine->GetGameHandler()->GetLoadedGame()->GetAuthors();
	if ( sAuthors.length() == 0 )
		sAuthors = "[Not specified]";

	pAuthors->SetText( sAuthors );

	m_pMenuList->AddObject( pAuthors );

	AddSeparator( 30 );

	m_pMenuList->AddObject(  m_pExitGame = new CSDLCenterTextObject( "GameDefaultLarge", "Exit Game", stGrey, stGrey ) );
}

CSDLStateGameMenu::~CSDLStateGameMenu()
{
	DebugInfo( TypeDelete, "Deleting game menu." );

	if ( m_pMenuList != 0 )
		delete m_pMenuList;
	m_pMenuList = 0;
}

void CSDLStateGameMenu::AddSeparator( int iHeight )
{
	SDL_Rect stSpacer = { 400, 400, 100, iHeight };
	
	CSDLHoverObject* pSeparator = new CSDLHoverObject;
	pSeparator->SetHoverDefaultRect( false );
	pSeparator->SetHoverRect( stSpacer );

	m_pMenuList->AddObject( pSeparator );
}

void CSDLStateGameMenu::Think( const int& iElapsedTime )
{
	CSDLBaseState::Think( iElapsedTime );

	m_pMenuList->Think( iElapsedTime );
}

void CSDLStateGameMenu::Render( SDL_Surface *pDestSurface ) 
{
	CSDLBaseState::Render( pDestSurface );

	m_pMenuList->Render( pDestSurface );
}

void CSDLStateGameMenu::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	m_pMenuList->MouseMoved( iButton, iX, iY );
}

void CSDLStateGameMenu::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	if ( m_pMenuList != 0 )
		m_pMenuList->MouseButtonDown( iButton, iX, iY );
}

void CSDLStateGameMenu::OnEnter( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnEnter( pObject );

	if ( pObject == m_pContinueGame ) {
		if ( m_bHasSaveGame == true ) {
			m_pDescription->SetText( "Continue the game from where you left off" );
		} else {
			m_pDescription->SetText( "Feature disabled - no save game is available" );
		}
	} else if ( pObject == m_pStartNewGame ) {
		m_pDescription->SetText( "Start a new game" );
	} else if ( pObject == m_pAgeRating ) {
		m_pDescription->SetText( "The approximated age rating for the game" );
	} else if ( pObject == m_pAuthors ) {
		m_pDescription->SetText( "List of the primary author(s) of the game" );
	} else if ( pObject == m_pExitGame ) {
		m_pDescription->SetText( "Go to the game list" );
	}
}

void CSDLStateGameMenu::OnLeave( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnLeave( pObject );
	if ( m_iObjectsWithFocus == 0 )
		m_pDescription->SetText( "" );
}

void CSDLStateGameMenu::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	CSDLBaseState::OnClicked( pObject, iButton );

	if ( pObject == m_pContinueGame ) 
	{
		if ( m_bHasSaveGame == true ) 
		{
			pEngine->GetLuaScriptHandler()->DoLuaFile( "Media\\" + pEngine->GetGameDir() + "\\SaveGame.was" );
			pEngine->GetLuaScriptHandler()->DoLuaScript( "StartLocation(Location)" );
		}
		else 
		{
			pEngine->GetLuaScriptHandler()->DoLuaScript( "ShowText('No save game is available.')" );
		}
	} 
	else if ( pObject == m_pStartNewGame ) 
	{
		string sStartLocation = pEngine->GetGameHandler()->GetLoadedGame()->GetStartLocation();

		if ( m_bHasSaveGame == true )
		{
			pEngine->GetLuaScriptHandler()->DoLuaScript( "ShowQuestion( \"Really sure to start a new game?\", \"Starting a new game will cause your saved progress to be lost.<br><br>Do you want to start a new game?\", \"StartLocation('" + sStartLocation + "')\" )" );
		}
		else 
		{
			pEngine->GetLuaScriptHandler()->DoLuaScript( "StartLocation( \"" + sStartLocation + "\" )" );
		}
	} 
	else if ( pObject == m_pAgeRating ) 
	{
		pEngine->GetLuaScriptHandler()->DoLuaScript( "ShowText(\"No need to click there<br>the text is already on the menu...\")" );
	} 
	else if ( pObject == m_pAuthors ) 
	{
		pEngine->GetLuaScriptHandler()->DoLuaScript( "ShowText(\"No need to click there<br>the text is already on the menu...\")" );
	} 
	else if ( pObject == m_pExitGame ) 
	{
		/*
		CSDLStateGameList* pGameList = new CSDLStateGameList;
		pGameList->LoadGameList( GetGameListURL() );

		pEngine->GetStateHandler()->NewLayerDelayedClear( pGameList );
		*/
		pEngine->GetLuaScriptHandler()->DoLuaScript( "ShowText(\"This feature doesn't work yet.<br><br>Unfortunately you'll have to restart<br>the application to get to the game list.<br><br>Sorry, my bad :(\")" );
	}
}