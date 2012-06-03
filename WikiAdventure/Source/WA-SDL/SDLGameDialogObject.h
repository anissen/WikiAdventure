
#ifndef SDLGAMEDIALOGOBJECT_H
#define SDLGAMEDIALOGOBJECT_H

#include "SDLMultilineTextObject.h"
#include "../Project/DialogObject.h"

const SDL_Color stWhite		= { 255, 255, 255 };
const SDL_Color stBlueish	= { 120, 110, 255 };
const SDL_Color stBlack		= { 0, 0, 0 };
const SDL_Color stNPC		= { 255, 90, 90 };

/** A ? object */
class CSDLGameDialogObject: public CSDLMultilineDebugTextObject
{
protected:
	CDialogObject* m_pDialog;
	bool m_bHeader;

public:
	CSDLGameDialogObject( CDialogObject* pDialog, const string& sFontID, bool bHeader = false, int iMaximumWidth = 600 );
	virtual ~CSDLGameDialogObject();

	virtual void OnMouseClicked( const int& iButton );

	virtual void SetText( const string& sText );

	CDialogObject* GetDialogObject() { return m_pDialog; };

	void LoadDialog();
};

/** A ? object */
/*
class CSDLGameDialogLine: public CSDLGameDialogObject
{
public:
	CSDLGameDialogLine( CDialogObject* pDialog, const string& sFontID )
		: CSDLMultilineDebugTextObject( sFontID, pDialog->GetDialogText(),
		stBlueBlack, 
		stBlack,
		stBlueish,
		stBlack,
		600) {};
	virtual ~CSDLGameDialogLine() {};
};
*/

#endif // SDLGAMEDIALOGOBJECT_H