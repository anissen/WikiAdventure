
#ifndef LOCATIONOBJECT_H
#define LOCATIONOBJECT_H

#include "IBaseObject.h"
#include "WebPage.h"
#include "ItemObject.h"
//#include "DialogObject.h"
#include "ItemHandler.h"
#include "DialogHandler.h"

#include <map>
using std::map;

/** A location object */
class CLocationObject: public IBaseLoadObject
{
protected:
	CImageHandler*	m_pImageHandler;
	string			m_sBackgroundImage;

	CItemHandler*	m_pItemHandler;
	CDialogHandler*	m_pDialogHandler;

public:
	CLocationObject();
	virtual ~CLocationObject();

	string GetBackgroundImage() { return m_sBackgroundImage; }

	CItemHandler*	GetItems()	{ return m_pItemHandler; }
	CItemObject*	GetItem( const string& sItemID )	{ return m_pItemHandler->GetItem( sItemID ); }

	CDialogHandler*	GetDialogs(){ return m_pDialogHandler; }
	CDialogObject*	GetDialog( const string& sDialogID ) { return m_pDialogHandler->GetDialog( sDialogID ); }

	void LoadContents( const string& sLocationPage );
	stLoadStatus LoadNext();
};

#endif // LOCATIONOBJECT_H