
#ifndef SDLDEBUGQUEUELIST_H
#define SDLDEBUGQUEUELIST_H

#include "SDLSizedQueueList.h"

/** A ? object */
class CSDLDebugQueueList: public CSDLSizedQueueList
{
protected:
	int m_iCountdownTime;
	int m_iTimeThreshold;

public:
	CSDLDebugQueueList();
	virtual ~CSDLDebugQueueList();

	virtual void Clear();
	virtual void Think( const int& iElapsedTime );
	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY ) {}; // Overwriting the mouse move event
};

#endif // SDLDEBUGQUEUELIST_H