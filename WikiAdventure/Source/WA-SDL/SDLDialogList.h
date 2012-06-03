
#ifndef SDLDIALOGLIST_H
#define SDLDIALOGLIST_H

#include "SDLTextSelectionList.h"
#include "../Project/DialogObject.h"
#include "SDLGameDialogObject.h"

/** A ? object */
class CSDLDialogList: public CSDLTextSelectionList
{
private:
	CDialogObject* m_pMainDialog;
	//CDialogObject* m_pCurrentDialog;
	bool m_bNoOptions;

public:
	CSDLDialogList();
	virtual ~CSDLDialogList();

	virtual void Load( CDialogObject* pDialog );

	void NewDialog( CDialogObject* pDialog );

	CDialogObject* GetMainDialog() { return m_pMainDialog; }

	virtual void OnClicked( CSDLBaseObject* pObject, const int& iButton );
};

#endif // SDLDIALOGLIST_H