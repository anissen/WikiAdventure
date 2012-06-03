
#ifndef SDLDEBUGOVERLAY_H
#define SDLDEBUGOVERLAY_H

#include "SDLDebugQueueList.h"
#include "SDLBaseTextObject.h"
#include "SDLTextSelectionList.h"

#include "SDLDebugTextObject.h"

static SDL_Color stInfo			= { 75, 75, 255 };
static SDL_Color stInfoBG		= { 255, 255, 255 };

static SDL_Color stWarning		= { 223, 118, 48 };
static SDL_Color stWarningBG	= { 235, 235, 235 };

static SDL_Color stError		= { 255, 0, 0 };
static SDL_Color stErrorBG		= { 0,   0, 0 };

/** A ? object */
class CSDLDebugOverlay: public ISDLUIContainerInterface
{
private:
	CSDLDebugQueueList*		m_pDebugList;
	CSDLBaseTextObject*		m_pFPSCounter;
	CSDLTextSelectionList*	m_pDebugOptions;

	CSDLBaseTextObject*		m_pTextReportBug;
	CSDLBaseTextObject*		m_pTextRequestFeature;
	CSDLBaseTextObject*		m_pTextEditGame;
	CSDLBaseTextObject*		m_pTextEditLocation;
	CSDLBaseTextObject*		m_pToggleHighlight;
	CSDLBaseTextObject*		m_pTextClearLog;
	CSDLBaseTextObject*		m_pTextHideDebug;
	CSDLBaseTextObject*		m_pTextSaveGame;
	CSDLBaseTextObject*		m_pTextBackToMenu;

	bool m_bHighlightRects;

public:
	CSDLDebugOverlay();
	virtual ~CSDLDebugOverlay();

	virtual void Render( SDL_Surface* pDestSurface );
	virtual void Think( const int& iElapsedTime );
	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void OnClicked( CSDLBaseObject* pObject, const int& iButton );

	void SetFPSValue( int iValue );

	bool GetShowHighlights() { return m_bHighlightRects; }

	virtual void AddObject	( CSDLBaseObject* pBaseObject );
	virtual void AddInfo	( const string& sText );
	virtual void AddWarning	( const string& sText );
	virtual void AddError	( const string& sText );
};

#endif // SDLDEBUGOVERLAY_H