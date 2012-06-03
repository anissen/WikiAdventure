
#include "SDLStateLoading.h"

CSDLStateLoading::CSDLStateLoading()
{
	DebugInfo( TypeCreate, "Creating loading screen." );

	m_iPosX = 400;
	m_iPosY = 250;

	m_pBackground = new CSDLBaseObject;
	m_pBackground->LoadImageFromFile( g_sAppDir + "\\Media\\WikiAdventure\\Loading.jpg" );

	m_pLoadText = new CSDLSizedQueueList;
	m_pLoadText->SetPos( m_iPosX, m_iPosY );
	m_pLoadText->AddObject( new CSDLCenterTextObject( "Default", "WikiAdventure is loading..." ) );
	m_pLoadText->AddObject( new CSDLCenterTextObject( "Default", "Please wait." ) );
}

CSDLStateLoading::~CSDLStateLoading()
{
	DebugInfo( TypeDelete, "Deleting loading screen." );

	if ( m_pLoadText != 0 )
		delete m_pLoadText;
}

void CSDLStateLoading::Think( const int& iElapsedTime )
{
	m_pLoadText->Think( iElapsedTime );
}

void CSDLStateLoading::Render( SDL_Surface *pDestSurface ) 
{
	CSDLBaseState::Render( pDestSurface );
	m_pLoadText->Render( pDestSurface );
	//SDL_Delay( 1000 );
}
