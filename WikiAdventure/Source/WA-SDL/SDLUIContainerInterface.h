
#ifndef SDLUICONTAINERINTERFACE_H
#define SDLUICONTAINERINTERFACE_H

#include "SDLBaseInterface.h"

/** A ? object */
class ISDLUIContainerInterface: public ISDLBaseInterface
{
public:
	ISDLUIContainerInterface() {};
	virtual ~ISDLUIContainerInterface() {};

	virtual void OnEnter	( CSDLBaseObject* pObject ) {};
	virtual void OnLeave	( CSDLBaseObject* pObject ) {};
	virtual void OnHovering	( CSDLBaseObject* pObject ) {};
	virtual void OnClicked	( CSDLBaseObject* pObject, const int& iButton ) {};
};

#endif // SDLUICONTAINERINTERFACE_H