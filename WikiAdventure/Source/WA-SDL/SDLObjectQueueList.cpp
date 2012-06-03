
#include "SDLObjectQueueList.h"

CSDLObjectQueueList::CSDLObjectQueueList()
{
	DebugInfo( TypeCreate, "Creating object queue list." );
}

CSDLObjectQueueList::~CSDLObjectQueueList()
{
	//DebugInfo( TypeDelete, "Unloading object queue list." );
	Clear();
}

void CSDLObjectQueueList::AddObject( CSDLBaseObject* pBaseObject )
{
	if ( pBaseObject == 0 )
	{
		DebugInfo( TypeWarning, "Added pointer to object is invalid." );
		// handle error
		return;
	}
	
	m_vpObjects.push_back( pBaseObject );

	if ( GetCallbackContainer() != 0 )
	{
		// Try setting the callback for the newly added object
		try {
			static_cast< CSDLHoverObject*>( pBaseObject )->SetCallbackContainer( GetCallbackContainer() );
		}
		catch ( ... ) {
			// The object dosn't inherit from CSDLHoverObject - just ignore it.
		}
	}
}

void CSDLObjectQueueList::Clear()
{
	while( m_vpObjects.size() > 0 )
	{
		if ( m_vpObjects.back() != 0 )
			delete m_vpObjects.back();

		m_vpObjects.pop_back();
	}
}

void CSDLObjectQueueList::Think( const int& iElapsedTime )
{
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		if ( m_vpObjects[i] == 0 ) {
			// some horrible error here
		} else {
			m_vpObjects[i]->Think( iElapsedTime );
		}
	}
}

CSDLBaseObject* CSDLObjectQueueList::GetObjectByIndex( unsigned int iObjectIndex )
{
	if ( (iObjectIndex < 0) || (iObjectIndex > m_vpObjects.size()) )
	{
		DebugInfo ( TypeWarning, "WRONG INDEX, JERK!" );
		return 0;
	}

	return m_vpObjects[ iObjectIndex ];
}

void CSDLObjectQueueList::Render( SDL_Surface* pDestSurface )
{
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		if ( m_vpObjects[i] == 0 ) {
			// some horrible error here
		} else {
			m_vpObjects[i]->Render( pDestSurface );
		}
	}
}

void CSDLObjectQueueList::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		m_vpObjects[i]->MouseMoved( iButton, iX, iY );
	}
}

void CSDLObjectQueueList::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		m_vpObjects[i]->MouseButtonDown( iButton, iX, iY );
	}
}

void CSDLObjectQueueList::SetCallbackContainer( ISDLUIContainerInterface* pContainerCallback )
{
	// Assign the callback for this object first
	CSDLHoverObject::SetCallbackContainer( pContainerCallback );

	// Then for all the contained objects.
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		try {
			static_cast< CSDLHoverObject*>( m_vpObjects[i] )->SetCallbackContainer( pContainerCallback );
		}
		catch ( ... ) {
			// The object dosn't inherit from CSDLHoverObject - just ignore it.
		}
	}
}