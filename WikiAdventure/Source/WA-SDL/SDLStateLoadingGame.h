
#ifndef SDLSTATELOADINGGAME_H
#define SDLSTATELOADINGGAME_H

#include "SDLBaseState.h"
#include "SDLTextSelectionList.h"
#include "SDLBaseTextObject.h"
#include "../Project/GameHandler.h"

class CSDLLoadTextObject: public CSDLBaseTextObject
{
protected:
	string	m_sLoadText;

public:
	CSDLLoadTextObject( const string& sLoadText, const string& sFont ): CSDLBaseTextObject( sFont, sLoadText )
	{
		m_sLoadText	 = sLoadText;
		SetVisible( false );
	}
	virtual ~CSDLLoadTextObject() {}

	virtual void Think( const int& iElapsedTime, int iNumber, int iCount )
	{
		char* czText = new char[ m_sLoadText.length() + 8 ];
		if ( iCount > 0 ) {
			sprintf( czText, m_sLoadText.c_str(), iNumber, iCount, (iNumber / (float)iCount) * 100 );
		} else {
			sprintf( czText, m_sLoadText.c_str(), iNumber, iCount, 100.00f );
		}
		SetText( czText );
		delete czText;

		SetVisible( true );
	}

	virtual void SetText( const string& sText )
	{
		CSDLBaseTextObject::SetText( sText );

		SetVisible( true );
	}
};

/** A ? object */
class CSDLStateLoadingGame: public CSDLBaseState
{
protected:
	CSDLTextSelectionList* m_pLoadText;
	CSDLBaseObject* pSeperator;

	CSDLLoadTextObject* m_pLoading;
	CSDLLoadTextObject*	m_pLocations;
	CSDLLoadTextObject*	m_psLocations;
	CSDLLoadTextObject* m_pItems;
	CSDLLoadTextObject* m_psItems;
	CSDLLoadTextObject* m_pDialogs;
	CSDLLoadTextObject* m_psDialogs;
	CSDLLoadTextObject* m_pFont;
	CSDLLoadTextObject* m_psFont;
	CSDLLoadTextObject* m_pImages;
	CSDLLoadTextObject* m_psImages;

	string				m_sGamePage;

	bool bDownloadedContents;
	bool bContentsLoading;
	bool m_bLoadComplete;

	int iLocationsLoaded;

	CSDLBaseTextObject* m_pContinue;

public:
	CSDLStateLoadingGame( const string& sGamePage );
	virtual ~CSDLStateLoadingGame();

	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
};

#endif // SDLSTATELOADINGGAME_H