
#ifndef SDLSTATEGAMELIST_H
#define SDLSTATEGAMELIST_H

#include "SDLBaseState.h"
#include "SDLTextSelectionList.h"

/** A ? object */
class CSDLStateGameList: public CSDLBaseState
{
protected:
	CSDLTextSelectionList*	m_pGameList;

public:
	CSDLStateGameList();
	virtual ~CSDLStateGameList();

	virtual void OnEnter( CSDLBaseObject* pObject );
	virtual void OnLeave( CSDLBaseObject* pObject );
	virtual void OnClicked ( CSDLBaseObject* pObject, const int& iButton );
	
	virtual void Think	( const int& iElapsedTime );
	virtual void Render	( SDL_Surface* pDestSurface );

	virtual void LoadGameList( const string& sGameListURL );
	virtual void AddGame( const string& sGameName );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );
};

#endif // SDLSTATEGAMELIST_H