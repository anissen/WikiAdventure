
#include "SDLDebugQueueList.h"

CSDLDebugQueueList::CSDLDebugQueueList(): CSDLSizedQueueList( 300 )
{
	//DebugInfo( "CSDLBaseObject", "CSDLBaseObject", "Info", "Creating base SDL object.", FILE_INFO );
	m_iPosX = 5;
	m_iPosY = 5;
	m_iAlpha = 150;
	m_iCountdownTime = 0;
	m_iTimeThreshold = 2000; // 1000 miliseconds = 1 second
}

CSDLDebugQueueList::~CSDLDebugQueueList()
{
	//DebugInfo( "CSDLBaseObject", "~CSDLBaseObject", "Info", "Unloading base SDL object.", FILE_INFO );
}

void CSDLDebugQueueList::Clear()
{
	m_iCountdownTime = 0;
	CSDLSizedQueueList::Clear();
}

void CSDLDebugQueueList::Think( const int& iElapsedTime )
{
	if ( m_vpObjects.size() > 0 )
	{
		m_iCountdownTime += iElapsedTime;
		if ( m_iCountdownTime >= m_iTimeThreshold )
		{
			m_iCountdownTime = 0;
			RemoveTopObject();
		}
	}
	else
	{
		m_iCountdownTime = 0;
	}

	CSDLSizedQueueList::Think( iElapsedTime );
}