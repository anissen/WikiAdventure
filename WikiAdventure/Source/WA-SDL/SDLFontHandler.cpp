
#include "SDLFontHandler.h"
#include "Globals.h"

CSDLFontHandler::CSDLFontHandler()
{
	DebugInfo( TypeCreate, "Creating font handler." );

	int iResult = TTF_Init();
	if( iResult == -1 ) {
		char czError[256];
		sprintf( czError, "Error: unable to initialize TTF_SDL, %s", TTF_GetError() );
		DebugInfo( TypeError, czError );
	}
}

CSDLFontHandler::~CSDLFontHandler()
{
	DebugInfo( TypeDelete, "Deleting font handler." );

	map<string, TTF_Font*>::iterator FontIter = m_mpFonts.begin();
	while ( FontIter != m_mpFonts.end() )
	{
		if ( FontIter->second != 0 )
		{
			DebugInfo( TypeInfo, string("Deleting font with ID \"" + FontIter->first + "\".").c_str() );
			TTF_CloseFont( FontIter->second );
		}

		++FontIter;
	}

	TTF_Quit();
}

bool CSDLFontHandler::AddFont( const string& sFontFile, const string& sFontID, int iSize )
{
	if ( m_mpFonts.count( sFontID ) && m_mpFonts[ sFontID ] != 0 )
	{
		DebugInfo( TypeWarning, string("Font with ID \"" + sFontID + "\" already defined!").c_str() );
		return false;
	}
	else
	{
		DebugInfo( TypeInfo, string("Creating new font with ID \"" + sFontID + "\" from file \"" + sFontFile + "\".").c_str() );
		// Load the font
		TTF_Font* pTempFont = TTF_OpenFont( sFontFile.c_str(), iSize );
		if( pTempFont != 0 ) 
		{
			m_mpFonts[ sFontID ] = pTempFont;
			return true;
		} else 	{
			DebugInfo( TypeWarning, "TTF_OpenFont error:" );
			DebugInfo( TypeWarning, TTF_GetError() );
			// handle error
			return false;
		}
	}
}

TTF_Font* CSDLFontHandler::GetFont( const string sFontID )
{
	if ( m_mpFonts.count( sFontID ) == 0 )
	{
		// IT DOSEN*T EXIST!
		// HANDLE THIS ERROR
		DebugInfo( TypeWarning, string("The requested front ID (\"" + sFontID + "\" dosen't exist!").c_str() );
		return 0;
	}
	return m_mpFonts[ sFontID ];
}

void CSDLFontHandler::RemoveFont( const string& sFontID )
{
	if ( m_mpFonts.count( sFontID ) )
	{
		DebugInfo( TypeInfo, string("Removing font with id \"" + sFontID + "\"!").c_str() );
		TTF_CloseFont( m_mpFonts[ sFontID ] );
		m_mpFonts.erase( sFontID );
	}
}