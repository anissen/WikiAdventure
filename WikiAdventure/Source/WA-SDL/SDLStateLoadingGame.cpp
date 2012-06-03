
#include "SDLStateLoadingGame.h"
#include "EngineMain.h"

#include "SDLStateGameMenu.h"

CSDLStateLoadingGame::CSDLStateLoadingGame( const string& sGamePage )
{
	DebugInfo( TypeCreate, "Creating game loading screen." );

	pEngine->SetTitle( "WikiAdventure - Loading Game" );

	// If the game's directory doesn't exist, then create it
	if ( !DoesGameDirExist( sGamePage ) ) {
		CreateGameDir( sGamePage );
	}
 
	pEngine->SetGameDir( sGamePage );

	pEngine->SetLocationOverlay( 0 ); // Reset the location overlay

	pEngine->SetInGame( false );

	m_sGamePage = sGamePage;

	bDownloadedContents = false;
	bContentsLoading	= false;
	m_bLoadComplete		= false;
	iLocationsLoaded	= 0;

	pSeperator = 0;

	m_iPosX = 100;
	m_iPosY = 190;

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "Loading.jpg" ) );

	m_pLoadText = new CSDLTextSelectionList;
	m_pLoadText->SetPos( m_iPosX, m_iPosY );

	m_pLoadText->AddObject( new CSDLBaseTextObject( "Default", "Downloading game contents..." ) );
}

CSDLStateLoadingGame::~CSDLStateLoadingGame()
{
	DebugInfo( TypeDelete, "Deleting game loading screen." );

	/*
	if ( m_pGameHandler != 0 )
		delete m_pGameHandler;
	m_pGameHandler = 0;
	*/

	if ( m_pLoadText != 0 )
		delete m_pLoadText;
	m_pLoadText = 0;
}

void CSDLStateLoadingGame::Think( const int& iElapsedTime )
{
	if ( bDownloadedContents == false ) 
	{
		pEngine->GetGameHandler()->LoadGame( m_sGamePage );
		
		bDownloadedContents = true;
	} 
	else if ( bContentsLoading == false ) 
	{
		m_pLoadText->Clear(); // Remove info about contents download

		m_pLoading		= new CSDLLoadTextObject( "%.2f Percent Complete",								"DefaultLarge" );
		m_pImages		= new CSDLLoadTextObject( "Loading image %d of %d (%.2f percent complete)",		"DefaultSmall" );
		m_pFont			= new CSDLLoadTextObject( "Loading font %d of %d (%.2f percent complete)",		"DefaultSmall" );
		m_pLocations	= new CSDLLoadTextObject( "Loading location %d of %d (%.2f percent complete)",	"DefaultSmall" );
		m_pItems		= new CSDLLoadTextObject( "Loading item %d of %d (%.2f percent complete)",		"DefaultSmall" );
		m_pDialogs		= new CSDLLoadTextObject( "Loading dialog %d of %d (%.2f percent complete)",	"DefaultSmall" );

		m_pLoadText->AddObject( m_pLoading );
		pSeperator = new CSDLBaseObject;
		pSeperator->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "SeparatorV.png" ) );
		m_pLoadText->AddObject( pSeperator );
		m_pLoadText->AddObject( m_pImages );
		m_pLoadText->AddObject( m_psImages		= new CSDLLoadTextObject( "-", "LoadText" ) );
		m_pLoadText->AddObject( m_pFont );
		m_pLoadText->AddObject( m_psFont		= new CSDLLoadTextObject( "-", "LoadText" ) );
		m_pLoadText->AddObject( m_pLocations );
		m_pLoadText->AddObject( m_psLocations	= new CSDLLoadTextObject( "-", "LoadText" ) );
		m_pLoadText->AddObject( m_pItems );
		m_pLoadText->AddObject( m_psItems		= new CSDLLoadTextObject( "-", "LoadText" ) );
		m_pLoadText->AddObject( m_pDialogs );
		m_pLoadText->AddObject( m_psDialogs		= new CSDLLoadTextObject( "-", "LoadText" ) );

		m_pLoading->SetText( "Loading " + m_sGamePage + "..." );

		SDL_Color stBlueish = { 100, 100, 255 };
		SDL_Color stWhite = { 255, 255, 255 };
		m_pContinue = new CSDLCenterTextObject( "Default", "Click to continue", stBlueish, stWhite );
		m_pContinue->SetVisible( false );
		m_pContinue->SetCallbackContainer( this );
		m_pContinue->SetPos( 400, 540 );
		this->AddObject( m_pContinue );

		bContentsLoading = true;
	} 
	else
	{
		CSDLLoadTextObject* pLoadObject = 0;
		CSDLLoadTextObject* pLoadStatus = 0;
		if ( pEngine->GetGameHandler()->GetLoadFinished() == false ) 
		{
			stLoadStatus stLoadInfo = pEngine->GetGameHandler()->LoadNext();

			switch ( stLoadInfo.eObjectLoaded ) {
			//case GameLoaded:		pLoadObject = m_pLoading;	break;
			case LocationLoaded:	pLoadObject = m_pLocations; pLoadStatus = m_psLocations; ++iLocationsLoaded; break;
			case DialogLoaded:		pLoadObject = m_pDialogs;	pLoadStatus = m_psDialogs;	 break;
			case ItemLoaded:		pLoadObject = m_pItems;		pLoadStatus = m_psItems;	 break;
			case ImageLoaded:		pLoadObject = m_pImages;	pLoadStatus	= m_psImages;	 break;
			case FontLoaded:		pLoadObject = m_pFont;		pLoadStatus = m_psFont;	     break;
			case FileLoaded:		pLoadObject = m_pFont;		pLoadStatus = m_psFont;	     break;
			}

			if ( pLoadObject != 0 )
				pLoadObject->Think( iElapsedTime, stLoadInfo.iNumberLoaded, stLoadInfo.iTotalCount );

			if ( pLoadStatus != 0 )
				pLoadStatus->SetText( "- " + stLoadInfo.sStatus );

			// Hack to determine when "Loading.jpg" and "SeparatorV.png" has been downloaded
			if ( stLoadInfo.eObjectLoaded == ImageLoaded && iLocationsLoaded == 1 ) {
				m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "Loading.jpg" ) );
				pSeperator->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), "SeparatorV.png" ) );
				++iLocationsLoaded;
			}
		}
		else if ( m_bLoadComplete == false )
		{
			FontHandler.RemoveFont( "DialogNPC" );
			FontHandler.AddFont( GetMediaPath( pEngine->GetGameDir(), "DialogNPC.ttf" ), "DialogNPC", 20 );

			FontHandler.RemoveFont( "Dialog" );
			FontHandler.AddFont( GetMediaPath( pEngine->GetGameDir(), "Dialog.ttf" ), "Dialog", 20 );

			FontHandler.RemoveFont( "GameDefault" );
			FontHandler.AddFont( GetMediaPath( pEngine->GetGameDir(), "Default.ttf" ), "GameDefault", 20 );

			FontHandler.RemoveFont( "GameDefaultSmall" );
			FontHandler.AddFont( GetMediaPath( pEngine->GetGameDir(), "Default.ttf" ), "GameDefaultSmall", 18 );

			FontHandler.RemoveFont( "GameDefaultLarge" );
			FontHandler.AddFont( GetMediaPath( pEngine->GetGameDir(), "Default.ttf" ), "GameDefaultLarge", 22 );

			m_pLoading->SetText( "Loading Complete!" );
			m_pContinue->SetVisible( true );

			CLocationObject* pLocation = pEngine->GetGameHandler()->GetLoadedGame()->GetLocations()->GetLocation( "Overlay" );
			if ( pLocation != 0 ) {
				CSDLStateLocation* pSDLLocation = new CSDLStateLocation;
				pSDLLocation->Load( pLocation );
				pEngine->SetLocationOverlay( pSDLLocation );
			}

			m_bLoadComplete = true;
		}
	}
}

void CSDLStateLoadingGame::Render( SDL_Surface *pDestSurface ) 
{
	CSDLBaseState::Render( pDestSurface );
	m_pLoadText->Render( pDestSurface );
}

void CSDLStateLoadingGame::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	// go to next state!
	if ( pObject == m_pContinue ) {
		pEngine->GetStateHandler()->NewLayerDelayedClear( new CSDLStateGameMenu );
	}
}
