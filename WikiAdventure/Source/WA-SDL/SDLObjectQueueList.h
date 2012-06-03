
#ifndef SDLOBJECTQUEUELIST_H
#define SDLOBJECTQUEUELIST_H

#include "SDLHoverObject.h"
#include "SDLUIContainerInterface.h"

#include <vector>
using std::vector;

/** A ? object */
class CSDLObjectQueueList: public CSDLHoverObject, public ISDLUIContainerInterface
{
protected:
	vector<CSDLBaseObject*>	m_vpObjects;

public:
	CSDLObjectQueueList();
	virtual ~CSDLObjectQueueList();

	virtual void AddObject( CSDLBaseObject* pBaseObject );
	CSDLBaseObject* GetObjectByIndex( unsigned int iObjectIndex );
	void Clear();

	unsigned int GetCount() { return m_vpObjects.size(); }

	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void MouseMoved		( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonUp	( const int& iButton, const int& iX, const int& iY ) {};
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void SetCallbackContainer( ISDLUIContainerInterface* pContainerCallback );
};

#endif // SDLOBJECTQUEUELIST_H