
#include "SDLTextSelectionList.h"

CSDLTextSelectionList::CSDLTextSelectionList()
{
	DebugInfo( TypeCreate, "Creating text selection list." );
	m_iHeaderEnd = 0;
	m_iHeight	 = 0;
	m_iWidth	 = 0;
}

CSDLTextSelectionList::~CSDLTextSelectionList()
{
	DebugInfo( TypeDelete, "Deleting text selection list." );
}

void CSDLTextSelectionList::AddHeader( CSDLBaseObject* pBaseObject )
{
	++m_iHeaderEnd;
	AddObject( pBaseObject );
}

void CSDLTextSelectionList::AddObject( CSDLBaseObject* pBaseObject )
{
	pBaseObject->SetPosX( m_iPosX );
	pBaseObject->SetAlpha( m_iAlpha );

	if ( m_vpObjects.size() > 0 )
	{
		pBaseObject->SetPosY( m_vpObjects[m_vpObjects.size()-1]->GetButtom() );
	}
	else
	{
		pBaseObject->SetPosY( m_iPosY );
	}

	m_iHeight += pBaseObject->GetHeight();

	if ( pBaseObject->GetWidth() > m_iWidth )
		m_iWidth = pBaseObject->GetWidth();

	CSDLObjectQueueList::AddObject( pBaseObject );
}

void CSDLTextSelectionList::SetPosX( int iPosX )
{
	// Move the objects to align with the new position
	for ( unsigned int i = 0; i < m_vpObjects.size(); ++i )
	{
		m_vpObjects[i]->SetPosX( iPosX );
	}

	CSDLObjectQueueList::SetPosX( iPosX );
}

void CSDLTextSelectionList::SetPosY( int iPosY )
{
	if ( m_vpObjects.size() > 0 )
	{
		// Move the objects to align with the new position
		m_vpObjects[0]->SetPosY( iPosY );

		for ( unsigned int i = 1; i < m_vpObjects.size(); ++i )
		{
			m_vpObjects[i]->SetPosY( m_vpObjects[i-1]->GetButtom() );
		}
	}

	CSDLObjectQueueList::SetPosY( iPosY );
}

void CSDLTextSelectionList::Clear()
{
	CSDLObjectQueueList::Clear();

	m_iHeaderEnd = 0;
	m_iHeight = 0;
	m_iWidth = 0;
}

void CSDLTextSelectionList::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	//m_pFocusObject = 0;
	for ( unsigned int i = m_iHeaderEnd; i < m_vpObjects.size(); ++i )
	{
		m_vpObjects[i]->MouseMoved( iButton, iX, iY );
	}
}

void CSDLTextSelectionList::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	//m_pChosenObject = 0;
	for ( unsigned int i = m_iHeaderEnd; i < m_vpObjects.size(); ++i )
	{
		if ( m_vpObjects[i] != 0 )
			m_vpObjects[i]->MouseButtonDown( iButton, iX, iY );
	}
}