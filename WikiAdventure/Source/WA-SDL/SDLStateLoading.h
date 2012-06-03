
#ifndef SDLSTATELOADING_H
#define SDLSTATELOADING_H

#include "SDLBaseState.h"
#include "SDLSizedQueueList.h"
#include "SDLBaseTextObject.h"

#include "../Project/Util.h"

/** A ? object */
class CSDLStateLoading: public CSDLBaseState
{
protected:
	CSDLSizedQueueList* m_pLoadText;

public:
	CSDLStateLoading();
	virtual ~CSDLStateLoading();

	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );
};

#endif // SDLSTATELOADING_H