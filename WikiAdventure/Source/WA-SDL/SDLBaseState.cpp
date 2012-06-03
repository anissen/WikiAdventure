
#include "SDLBaseState.h"

CSDLBaseState::CSDLBaseState()
{
	DebugInfo( TypeCreate, "Creating base state." );
	m_iObjectsWithFocus = 0;
	m_pBackground = 0;
	m_pDescription = 0;

	m_iPosX = 100;
	m_iPosY = 190;
}

CSDLBaseState::~CSDLBaseState()
{
	DebugInfo( TypeDelete, "Unloading base state." );

	if ( m_pDescription != 0 )
		delete m_pDescription;
	m_pDescription = 0;

	if ( m_pBackground != 0 )
		delete m_pBackground;
	m_pBackground = 0;
}

void CSDLBaseState::Think( const int& iElapsedTime )
{
	CSDLObjectQueueList::Think( iElapsedTime );
}

void CSDLBaseState::Render( SDL_Surface *pDestSurface ) 
{
	if ( m_pBackground != 0 )
		m_pBackground->Render( pDestSurface );
	
	CSDLObjectQueueList::Render( pDestSurface );

	if ( m_pDescription != 0 )
		m_pDescription->Render( pDestSurface );
}

void CSDLBaseState::OnEnter( CSDLBaseObject* pObject )
{
	++m_iObjectsWithFocus;
}

void CSDLBaseState::OnLeave( CSDLBaseObject* pObject )
{
	--m_iObjectsWithFocus;
}