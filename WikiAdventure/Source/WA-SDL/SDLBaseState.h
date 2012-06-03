
#ifndef SDLBASESTATE_H
#define SDLBASESTATE_H

#include "SDLObjectQueueList.h"
#include "SDLBaseTextObject.h"
#include "SDLCenterTextObject.h"
#include "SDLGameItemObject.h"
#include "SDLDialogList.h"

/** A ? object */
class CSDLBaseState: public CSDLObjectQueueList
{
protected:
	CSDLBaseObject*		m_pBackground;
	CSDLBaseTextObject*	m_pDescription;
	int m_iObjectsWithFocus;

public:
	CSDLBaseState();
	virtual ~CSDLBaseState();

	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void OnEnter( CSDLBaseObject* pObject );
	virtual void OnLeave( CSDLBaseObject* pObject );
};

#endif // SDLBASESTATE_H