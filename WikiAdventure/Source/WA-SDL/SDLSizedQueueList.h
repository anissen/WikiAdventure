
#ifndef SDLSIZEDQUEUELIST_H
#define SDLSIZEDQUEUELIST_H

#include "SDLObjectQueueList.h"

/** A ? object */
class CSDLSizedQueueList: public CSDLObjectQueueList
{
protected:
	int m_iMaxHeight;

public:
	CSDLSizedQueueList( int iMaxHeight = 200 );
	virtual ~CSDLSizedQueueList();

	virtual void AddObject( CSDLBaseObject* pBaseObject );
	void RemoveTopObject();
};

#endif // SDLSIZEDQUEUELIST_H