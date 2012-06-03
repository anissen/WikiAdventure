
#ifndef SDLGAMEITEMOBJECT_H
#define SDLGAMEITEMOBJECT_H

#include "SDLHoverObject.h"

/** A ? object */
class CSDLGameItemObject: public CSDLHoverObject
{
protected:
	string m_sDescription;
	string m_sOnLoad;
	string m_sOnClick;

public:
	CSDLGameItemObject();
	virtual ~CSDLGameItemObject();

	virtual void OnMouseClicked( const int& iButton );

	void	SetDescription( const string& sDescription ) { m_sDescription = sDescription; };
	string	GetDescription() { return m_sDescription; };

	void	SetOnLoad( const string& sOnLoad ) { m_sOnLoad = sOnLoad; }
	string	GetOnLoad()		{ return m_sOnLoad; }

	void LoadItem();

	void	SetOnClick( const string& sOnClick ) { m_sOnClick = sOnClick; }
	string	GetOnClick()	{ return m_sOnClick; }
};

#endif // SDLGAMEITEMOBJECT_H