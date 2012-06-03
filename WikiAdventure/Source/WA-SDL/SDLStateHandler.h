
#ifndef SDLSTATEHANDLER_H
#define SDLSTATEHANDLER_H

#include "SDLObjectQueueList.h"

/** A ? object */
class CSDLStateHandler: public ISDLUIContainerInterface
{
protected:
	vector<CSDLObjectQueueList*> m_vpLayers;
	bool bNewLayerNextFrame;
	int iDelayedPop;

	vector<CSDLObjectQueueList*> m_vpPopLayers;

	virtual void Validate();

public:
	CSDLStateHandler();
	virtual ~CSDLStateHandler();

	virtual void Render( SDL_Surface* pDestSurface );
	virtual void Think ( const int& iElapsedTime );

	virtual void MouseMoved		( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonUp	( const int& iButton, const int& iX, const int& iY ) {};
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void PushLayer( CSDLObjectQueueList* pLayer );
	virtual void PopLayer ();
	virtual void ClearLayers();

	virtual void NewLayerDelayedClear( CSDLObjectQueueList* pLayer );

	virtual void DelayedPopLayer( CSDLObjectQueueList* pLayer );

	virtual void DelayedPopLayer ();

	//virtual void SetNewLayerFlag() { bNewLayerNextFrame = true; }

	virtual void NewLayer( CSDLObjectQueueList* pLayer  );
};

#endif // SDLSTATEHANDLER_H