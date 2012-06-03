
#ifndef SDLSTATEQUESTIONBOX_H
#define SDLSTATEQUESTIONBOX_H

#include "SDLBaseState.h"
#include "SDLMultilineTextObject.h"

/** A ? object */
class CSDLStateQuestionBox: public CSDLBaseState
{
private:
	void InitMsgBox( const string& sTitle, const string& sMessage );

protected:
	CSDLBaseTextObject* m_pTitle;
	CSDLMultilineTextObject* m_pMessage;
	CSDLBaseTextObject* m_pButtonYes;
	CSDLBaseTextObject* m_pButtonNo;
	string m_sOnYesScript;
	string m_sOnNoScript;

	int m_iSelected;

public:
	CSDLStateQuestionBox( const string& sTitle, const string& sMessage );
	CSDLStateQuestionBox( const string& sTitle, const string& sMessage, const string& sOnYesScript );
	CSDLStateQuestionBox( const string& sTitle, const string& sMessage, const string& sOnYesScript, const string& sOnNoScript );
	virtual ~CSDLStateQuestionBox();

	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
};

#endif // SDLSTATEQUESTIONBOX_H