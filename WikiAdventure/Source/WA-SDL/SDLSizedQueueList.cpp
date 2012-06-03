
#include "SDLSizedQueueList.h"

CSDLSizedQueueList::CSDLSizedQueueList( int iMaxHeight )
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_iMaxHeight = iMaxHeight;
	m_iPosX = 5;
	m_iPosY = 5;
	m_iAlpha = 150;
}

CSDLSizedQueueList::~CSDLSizedQueueList()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
}

void CSDLSizedQueueList::AddObject( CSDLBaseObject* pBaseObject )
{
	pBaseObject->SetPos( m_iPosX, m_iPosY );
	pBaseObject->SetAlpha( m_iAlpha );

	if ( m_vpObjects.size() == 0 )
	{
		pBaseObject->SetPosY( m_iPosY );
	}
	else
	{
		int iObjectPosY;
		while( true )
		{
			iObjectPosY = m_vpObjects[m_vpObjects.size()-1]->GetButtom();
			if ( (iObjectPosY + pBaseObject->GetHeight()) <= (m_iPosY + m_iMaxHeight) )
				break;

			RemoveTopObject();
			
			if ( m_vpObjects.size() == 0 )
				throw std::exception( "WRONG RECT DEFINED FOR CSDLSIZEDQUEUELIST... jerk!" );
		}
		pBaseObject->SetPosY( iObjectPosY );
	}

	CSDLObjectQueueList::AddObject( pBaseObject );
}

void CSDLSizedQueueList::RemoveTopObject()
{
	if ( m_vpObjects.size() > 0 )
	{
		if ( m_vpObjects.front() != 0 )
			delete m_vpObjects.front();
		m_vpObjects.erase( m_vpObjects.begin() );

		if ( m_vpObjects.size() > 0 )
		{
			m_vpObjects[0]->SetPosY( m_iPosY );
			for ( unsigned int i = 1; i < m_vpObjects.size(); ++i )
			{
				m_vpObjects[i]->SetPosY( m_vpObjects[i-1]->GetButtom() );
			}
		}
	}
}
