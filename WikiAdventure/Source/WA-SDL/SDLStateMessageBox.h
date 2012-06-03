
#ifndef SDLSTATEMESSAGEBOX_H
#define SDLSTATEMESSAGEBOX_H

#include "SDLBaseState.h"
#include "SDLMultilineTextObject.h"

/** A ? object */
class CSDLStateMessageBox: public CSDLBaseState
{
private:
	void InitMsgBox( const string& sTitle, const string& sMessage );

protected:
	CSDLBaseTextObject* m_pTitle;
	CSDLMultilineTextObject* m_pMessage;
	CSDLBaseTextObject* m_pButtonOkay;
	string m_sOnExitScript;

public:
	CSDLStateMessageBox( const string& sTitle, const string& sMessage );
	CSDLStateMessageBox( const string& sTitle, const string& sMessage, const string& sOnExitScript );
	virtual ~CSDLStateMessageBox();

	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
};

#endif // SDLSTATEMESSAGEBOX_H