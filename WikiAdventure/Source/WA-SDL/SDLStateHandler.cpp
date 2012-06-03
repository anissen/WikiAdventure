
#include "SDLStateHandler.h"

CSDLStateHandler::CSDLStateHandler()
{
	DebugInfo( TypeCreate, "Creating state handler." );

	bNewLayerNextFrame = false;
	iDelayedPop = 0;
}

CSDLStateHandler::~CSDLStateHandler()
{
	DebugInfo( TypeDelete, "Deleting state handler." );

	ClearLayers();
}

void CSDLStateHandler::Render( SDL_Surface* pDestSurface )
{
	Validate();
	for ( unsigned int i = 0; i < m_vpLayers.size(); ++i )
	{
		m_vpLayers[i]->Render( pDestSurface );
	}
}

void CSDLStateHandler::Think( const int& iElapsedTime )
{
	while ( iDelayedPop > 0 && m_vpLayers.size() > 0 )
	{
		PopLayer();
		--iDelayedPop;
	}
	iDelayedPop = 0;

	while ( m_vpPopLayers.size() > 0 ) {
		for ( unsigned int i = 0; i < m_vpLayers.size(); ++i ) {
			if ( m_vpLayers[i] == m_vpPopLayers.back() ) {
				m_vpLayers.erase( m_vpLayers.begin() + i ); // erase the i'th element
				m_vpPopLayers.pop_back();
				break;
			}
		}
	}
	
	if ( bNewLayerNextFrame ) {
		CSDLObjectQueueList* pNewLayer = m_vpLayers.back();
		m_vpLayers.pop_back();
		NewLayer( pNewLayer );
		bNewLayerNextFrame = false;
	}
	
	Validate();
	if ( m_vpLayers.size() > 0 ) {
		m_vpLayers.back()->Think( iElapsedTime );
	}
}

void CSDLStateHandler::PushLayer( CSDLObjectQueueList* pLayer )
{
	if ( pLayer != 0 ) {
		m_vpLayers.push_back( pLayer );
	}
}

void CSDLStateHandler::PopLayer()
{
	if ( m_vpLayers.size() > 0 ) {
		if ( m_vpLayers.back() == 0 ) {
			m_vpLayers.pop_back();
		} else {
			// A little trick to avoid deleting any layers pushed using OnExit scripts
			CSDLObjectQueueList* pTemp = m_vpLayers.back();
			m_vpLayers.pop_back();
			delete pTemp;
		}
	}
}

void CSDLStateHandler::ClearLayers()
{
	while ( m_vpLayers.size() > 0 )	{
		PopLayer();
	}
}

void CSDLStateHandler::NewLayer( CSDLObjectQueueList* pLayer )
{
	ClearLayers();
	PushLayer( pLayer );
}

void CSDLStateHandler::NewLayerDelayedClear( CSDLObjectQueueList* pLayer )
{
	bNewLayerNextFrame = true;
	PushLayer( pLayer );
}

void CSDLStateHandler::DelayedPopLayer()
{
	++iDelayedPop;
}

void CSDLStateHandler::DelayedPopLayer( CSDLObjectQueueList* pLayer )
{
	m_vpPopLayers.push_back( pLayer );
}

void CSDLStateHandler::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	Validate();
	if ( m_vpLayers.size() > 0 ) {
		m_vpLayers.back()->MouseMoved( iButton, iX, iY );
	}
}

void CSDLStateHandler::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	Validate();
	if ( m_vpLayers.size() > 0 && m_vpLayers.back() != 0 ) {
		m_vpLayers.back()->MouseButtonDown( iButton, iX, iY );
	}
}

void CSDLStateHandler::Validate()
{
	// Remove all layers that have been destroyed (NULL pointers)
	while ( m_vpLayers.size() > 0 && m_vpLayers.back() == 0 ) {
		PopLayer();
	}
}