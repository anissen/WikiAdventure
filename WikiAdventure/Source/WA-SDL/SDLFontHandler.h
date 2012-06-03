
#ifndef SDLFONTHANDLER_H
#define SDLFONTHANDLER_H

#include <string>
using std::string;

#include <map>
using std::map;

#include "SDL_ttf.h"

/** A ? object */
class CSDLFontHandler
{
protected:
	map<string, TTF_Font*> m_mpFonts;

public:
	CSDLFontHandler();
	virtual ~CSDLFontHandler();

	bool		AddFont( const string& sFontFile, const string& sFontID, int iSize = 20 );
	TTF_Font*	GetFont( const string sFontID );

	void		RemoveFont( const string& sFontID );
};

#endif // SDLFONTHANDLER_H