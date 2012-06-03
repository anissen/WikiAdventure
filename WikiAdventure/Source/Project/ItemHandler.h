
#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H

#include "IBaseObject.h"
#include "ItemObject.h"
#include "WikiContent.h"

#include <map>
using std::map;

/** A location object */
class CItemHandler: public IBaseLoadObject
{
protected:
	map<string, CItemObject*>	m_mpItems;

	CWikiContent*				m_pItemList;
	IBaseLoadObject*			m_pItemLoading;

	map<string, CItemObject*>::iterator m_LoadIter;

public:
	CItemHandler();
	virtual ~CItemHandler();

	unsigned int GetCount() { return m_mpItems.size(); }
	CItemObject* GetNextItem();

	CItemObject* GetItem( const string& sItemID ) { return m_mpItems[ sItemID ]; }

	void ResetIteration();

	void LoadContents( const string& sRawItemData );
	stLoadStatus LoadNext();
};

#endif // ITEMHANDLER_H