
#include "Engine.h"

#include "SDLStateGameList.h"
#include "SDLStateLoading.h"
#include "SDLStateLocation.h"
#include "SDLDebugOverlay.h"
#include "SDLStateHandler.h"
#include "SDLGameDialogObject.h"

#include "ExceptionClasses.h"

#include "../Project/GameHandler.h"

#include "SDLStateMessageBox.h"
#include "SDLStateShowPicture.h"
#include "SDLStateShowText.h"
#include "SDLStateQuestionBox.h"

#include "../Project/LuaScriptHandler.h"

class CMyEngine: public CEngine
{
public:
	bool bDebugMode;

protected:
	CSDLStateHandler*		pStateHandler;
	CSDLDebugOverlay*		pDebugOverlay;
	CLuaScriptHandler*		pLuaScriptHandler;
	CSDLStateLocation*		m_pCurrentLocation;
	CGameHandler*			m_pGameHandler;
	
	string					m_sGameDir;
	string					m_sCurrentLocationName;

	CSDLGameItemObject*		m_pCurrentItem;

	CSDLGameDialogObject*	m_pCurrentDialog;
	CSDLDialogList*			m_pCurrentDialogList;

	CSDLStateLocation*		m_pLocationOverlay;

	bool					m_bInGame;

protected:
	void AdditionalInit();

	void Think			( const int& iElapsedTime );
	void Render			( SDL_Surface* pDestSurface );

	void KeyUp			(const int& iKeyEnum);
	void KeyDown		(const int& iKeyEnum);

	void End();

	void MouseMoved		(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY);
	void MouseButtonUp	(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY);
	void MouseButtonDown(const int& iButton, const int& iX, const int& iY, const int& iRelX, const int& iRelY);

public:
	CMyEngine();
	virtual ~CMyEngine();

	CSDLStateHandler* GetStateHandler()		{ return pStateHandler; }
	CSDLDebugOverlay* GetDebugOverlay()		{ return pDebugOverlay; }
	CLuaScriptHandler* GetLuaScriptHandler(){ return pLuaScriptHandler; }

	void SetCurrentLocation( CSDLStateLocation* pCurrentLocation ) { m_pCurrentLocation = pCurrentLocation; }
	CSDLStateLocation* GetCurrentLocation()	{ return m_pCurrentLocation; } 

	CGameHandler*	GetGameHandler() { return m_pGameHandler; }

	void SetGameDir( const string& sGameDir ) { m_sGameDir = sGameDir; }
	string GetGameDir()	{ return m_sGameDir; }

	void SetCurrentLocationName( const string& sCurrentLocationName ) { m_sCurrentLocationName = sCurrentLocationName; }
	string GetCurrentLocationName()	{ return m_sCurrentLocationName; }

	void SetCurrentItem( CSDLGameItemObject* pCurrentItem ) { m_pCurrentItem = pCurrentItem; }
	CSDLGameItemObject* GetCurrentItem() { return m_pCurrentItem; }

	void SetCurrentDialog( CSDLGameDialogObject* pCurrentDialog ) { m_pCurrentDialog = pCurrentDialog; }
	CSDLGameDialogObject* GetCurrentDialog() { return m_pCurrentDialog; }

	void SetCurrentDialogList( CSDLDialogList* pCurrentDialogList ) { m_pCurrentDialogList = pCurrentDialogList; }
	CSDLDialogList* GetCurrentDialogList() { return m_pCurrentDialogList; }

	void SetLocationOverlay( CSDLStateLocation* pLocationOverlay ) 	{ m_pLocationOverlay = pLocationOverlay; }
	CSDLStateLocation* GetLocationOverlay() { return m_pLocationOverlay; }

	void SetInGame( bool bInGame ) { m_bInGame = bInGame; }
	bool GetInGame() { return m_bInGame; }
};

extern CMyEngine* pEngine;