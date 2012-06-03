
#ifndef SDLSTATEGAMEMENU_H
#define SDLSTATEGAMEMENU_H

#include "SDLBaseState.h"
#include "SDLTextSelectionList.h"

/** A ? object */
class CSDLStateGameMenu: public CSDLBaseState
{
protected:
	CSDLCenterTextObject* m_pContinueGame;
	CSDLCenterTextObject* m_pStartNewGame;
	CSDLCenterTextObject* m_pAgeRating;
	CSDLCenterTextObject* m_pAuthors;
	CSDLCenterTextObject* m_pExitGame;

	CSDLTextSelectionList* m_pMenuList;

	bool m_bHasSaveGame;

	void AddSeparator( int iHeight );

public:
	CSDLStateGameMenu();
	virtual ~CSDLStateGameMenu();

	virtual void OnEnter( CSDLBaseObject* pObject );
	virtual void OnLeave( CSDLBaseObject* pObject );
	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );

	void MouseMoved( const int& iButton, const int& iX, const int& iY );

	void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
	
	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );
};

#endif // SDLSTATEGAMEMENU_H