
#ifndef SDL_GLOBALS_H
#define SDL_GLOBALS_H

#include "Singleton.h"
#include "SDLFontHandler.h"
#include "Graphics.h"

typedef Singleton<CSDLFontHandler> FontHandler;
#define FontHandler FontHandler::Instance()

typedef Singleton<CGraphics> Graphics;
#define Graphics Graphics::Instance()

static const enum eDebugType { TypeInfo, TypeWarning, TypeError, TypeCreate, TypeDelete };

//#define DebugInfo(eType,czText) ;
#define DebugInfo(eType,czText) WriteDebugData((eType),__FILE__,__FUNCTION__,__LINE__,(czText))

extern void WriteDebugData( const eDebugType eType, const char* czFile, const char* czFunction, const long lLine, const char* czText );

extern string g_sAppDir;

#endif // SDL_GLOBALS_H
