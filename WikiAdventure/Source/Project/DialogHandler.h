
#ifndef DIALOGHANDLER_H
#define DIALOGHANDLER_H

#include "IBaseObject.h"
#include "DialogObject.h"
#include "WikiContent.h"

#include <map>
using std::map;

/** A location object */
class CDialogHandler: public IBaseLoadObject
{
protected:
	map<string, CDialogObject*>		m_mpDialogs;

	CWikiContent*					m_pDialogList;
	IBaseLoadObject*				m_pDialogLoading;

public:
	CDialogHandler();
	virtual ~CDialogHandler();

	CDialogObject* GetDialog( const string& sDialogID );

	void LoadContents( const string& sRawDialogBlock );
	stLoadStatus LoadNext();
};

#endif // DIALOGHANDLER_H