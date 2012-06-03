
#ifndef SDLSTATELOCATION_H
#define SDLSTATELOCATION_H

#include "SDLBaseState.h"
#include "../Project/LocationObject.h"

/** A ? object */
class CSDLStateLocation: public CSDLBaseState
{
protected:
	CLocationObject* m_pLocationObject;

public:
	CSDLStateLocation();
	virtual ~CSDLStateLocation();

	virtual void Load( CLocationObject* pLocation  );

	virtual void StartDialog( const string& sDialogID );

	virtual void OnEnter( CSDLBaseObject* pObject );
	virtual void OnLeave( CSDLBaseObject* pObject );
	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );

	virtual CLocationObject* GetLocationObject() { return m_pLocationObject; }
};

#endif // SDLSTATELOCATION_H