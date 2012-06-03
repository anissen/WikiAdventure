

#ifndef UTIL_H
#define UTIL_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Shlwapi.h"	// For the PathFileExists function
#include <direct.h>		// For the mkdir-function

#include "../WA-SDL/Globals.h"
//#include "Globals.h"

/** Get text between two specified tags.
	@param	sText The text that should be searched.
	@param	sStartTag The starting tag.
	@param	sEndTag	The ending tag.
	@return A string containing the text between the first occurrence of the two tags. Returns a zero-length string on failure.
*/
static string GetTaggedText( const string& sText, const string& sStartTag, const string& sEndTag )
{
	size_t lStart = sText.find( sStartTag, 0 );
	if ( lStart == string::npos ) 
	{
		return string("");
	}
	
	// Make sure that the start tag isn't included in the returned text
	lStart += sStartTag.length();
	
	size_t lEnd = sText.find( sEndTag, lStart );
	if ( lEnd == string::npos ) 
	{
		return string("");
	}
	return sText.substr( lStart, lEnd - lStart );
}

/** Get text between specified tags.
	@param	sText The text that should be searched.
	@param	sTag The start tag will is <sTag> and the end tag is </sTag>.
	@return A string containing the text between the first occurrence of the two tags. Returns a zero-length string on failure.
*/
static string GetTaggedText( const string& sText, const string& sTag )
{
	return GetTaggedText( sText, "<" + sTag + ">", "</" + sTag + ">" );
}

/** Get text between specified tags, and a selected default text on failure.
	@param	sText The text that should be searched.
	@param	sTag The start tag will is <sTag> and the end tag is </sTag>.
	@return A string containing the text between the first occurrence of the two tags. Returns a the chosen default text on failure.
*/
static string GetTaggedText( const string& sText, const string& sStartTag, const string& sEndTag, const string& sDefault )
{
	string sTemp = GetTaggedText( sText, sStartTag, sEndTag );

	if ( sTemp.length() == 0 ) {
		return sDefault;
	} else {
		return sTemp;
	}
}

/** Get text between all occurrences of the two specified tags.
	@param	sText The text that should be searched.
	@param	sStartTag The starting tag.
	@param	sEndTag	The ending tag.
	@return A vector array of strings containing the found text.
*/
static vector<string> GetTaggedTextArray( const string& sText, const string& sStartTag, const string& sEndTag )
{
	vector<string> vTextArray;
	size_t lStart = 0;
	size_t lEnd	 = 0;
	
	while( true )
	{
		lStart = sText.find( sStartTag, lStart );
		if ( lStart == string::npos ) 
		{
			break;
		}
		
		// Make sure that the start tag isn't included in the returned text
		lStart += sStartTag.length();
		
		lEnd = sText.find( sEndTag, lStart );
		if ( lEnd == string::npos ) 
		{
			break;
		}
		
		vTextArray.push_back( sText.substr( lStart, lEnd - lStart ) );
	}
	return vTextArray;
}

/** Get text between all occurrences of the two specified tags.
	@param	sText The text that should be searched.
	@param	sTag The start tag will is <sTag> and the end tag is </sTag>.
	@return A vector array of strings containing the found text.
*/
static vector<string> GetTaggedTextArray( const string& sText, const string& sTag )
{
	return GetTaggedTextArray( sText, "<" + sTag + ">", "</" + sTag + ">" );
}

/** Parse a text string into an array separated by another text string
@param	sText The text that should be parsed.
@param	sSeparator The separator text.
@return A vector array of strings containing the parsed text.
*/
static vector<string> GetSeperatedTextArray( const string& sText, const string& sSeparator )
{
	vector<string> vTextArray;
	size_t lStart = 0;
	size_t lPos	  = 0;

	while( true )
	{
		lPos = sText.find( sSeparator, lStart );
		if ( lPos == string::npos ) 
		{
			// Put the text after the last separator into the array as well
			vTextArray.push_back( sText.substr( lStart, sText.length() - lStart ) );
			break;
		}

		vTextArray.push_back( sText.substr( lStart, lPos - lStart ) );

		lStart = lPos + sSeparator.length();
	}
	return vTextArray;
}

/** Removes all occurrences of a string for a text.
	@param	sText The text that should be searched.
	@param	sRemove The word that should be removed.
	@return The processed text.
*/
static string RemoveFromText( const string& sText, const string& sRemove )
{
	size_t lStart = 0;
	string sNewText = sText;

	while( true )
	{
		lStart = sNewText.find( sRemove, lStart );
		if ( lStart == string::npos ) 
			break;

		sNewText.erase( lStart, sRemove.length() );
	}
	return sNewText;
}

/** Replaces all occurrences of a string for a text.
	@param	sText The text that should be searched.
	@param	sReplace The word that should be replaced.
	@param	sReplaceWith The word it should be replaced with.
	@return The processed text.
*/
static string ReplaceInText( const string& sText, const string& sReplace, const string& sReplaceWith )
{
	size_t lStart = 0;
	string sNewText = sText;

	while( true )
	{
		lStart = sNewText.find( sReplace, lStart );
		if ( lStart == string::npos ) 
			break;

		sNewText.replace( lStart, sReplace.length(), sReplaceWith );
		lStart += sReplaceWith.length();
	}
	return sNewText;
}

/** Replaces all occurrences of "<br>" and "[br]" in the text.
	@return The processed text.
*/
static string ReplaceBR( const string& sText )
{
	return ReplaceInText( ReplaceInText( sText, "<br>", "\n" ), "[br]", "\n" );
}

/** Get the text after the last occurrence of a specified separator word.
	@param	sText The text that should be searched.
	@param	sSeparator The separator word.
	@return The text after the last occurrence of a specified separator word. Returns a zero-length string on failure.
*/
static string GetAfterLast( const string& sText, const string& sSeparator )
{
	size_t lPos = sText.rfind( sSeparator, sText.length() );

	if ( lPos == string::npos )
		return string("");

	lPos += sSeparator.length();
	
	return sText.substr( lPos, sText.length() - lPos );
}

/** Get the text after the first occurrence of a specified separator word.
	@param	sText The text that should be searched.
	@param	sSeparator The separator word.
	@return The text after the first occurrence of a specified separator word. Returns a zero-length string on failure.
*/
static string GetAfterFirst( const string& sText, const string& sSeparator )
{
	size_t lPos = sText.find( sSeparator, 0 );

	if ( lPos == string::npos )
		return string("");

	lPos += sSeparator.length();

	return sText.substr( lPos, sText.length() - lPos );
}

/** Get all text until the last occurrence of a specified separator word.
	@param	sText The text that should be searched.
	@param	sSeparator The separator word.
	@return The text until the last occurrence of a specified separator word. Returns a zero-length string on failure.
*/
static string GetUntilLast( const string& sText, const string& sSeparator )
{
	size_t lPos = sText.rfind( sSeparator, sText.length() );

	if ( lPos == string::npos )
		return string("");

	return sText.substr( 0, lPos );
}

/** Get all text until the first occurrence of a specified separator word.
	@param	sText The text that should be searched.
	@param	sSeparator The separator word.
	@return The text until the first occurrence of a specified separator word. Returns a zero-length string on failure.
*/
static string GetUntilFirst( const string& sText, const string& sSeparator )
{
	size_t lPos = sText.find( sSeparator, 0 );

	if ( lPos == string::npos )
		return string("");

	return sText.substr( 0, lPos );
}

/** Remove all the leading spaces from the text.
@param	sText The text that should be searched.
@return The processed text without leading spaces. Original text is returned on failure.
*/
static string RemoveLeadingSpaces( const string& sText )
{
	size_t lPos = sText.find_first_not_of( ' ' );

	if ( lPos == string::npos )
		return sText;

	return sText.substr( lPos, sText.length() - lPos );
}

static BOOL DoesMediaExist( const string& sMediaFileName )
{
	string sPath = g_sAppDir + "\\Media\\" + sMediaFileName;
	return PathFileExists( sPath.c_str() );
}

static BOOL DoesGameMediaExist( const string& sGame, const string& sMediaFileName )
{
	string sPath = g_sAppDir + "\\Media\\" + sGame + "\\" + sMediaFileName;
	return PathFileExists( sPath.c_str() );
}

static BOOL DoesGameDirExist( const string& sGame )
{
	string sPath = g_sAppDir + "\\Media\\" + sGame;
	return PathFileExists( sPath.c_str() );
}

static void CreateGameDir( const string& sGame )
{
	string sPath = g_sAppDir + "\\Media\\" + sGame;
	mkdir( sPath.c_str() );
}

static string GetMediaPath( const string& sGameDir, const string& sMediaFileName )
{
	if ( DoesGameMediaExist( sGameDir, sMediaFileName ) ) {
		return g_sAppDir + "\\Media\\" + sGameDir + "\\" + sMediaFileName;
	} else if ( DoesGameMediaExist( "Default", sMediaFileName ) ) {
		return g_sAppDir  + "\\Media\\Default\\" + sMediaFileName;
	} else {
		DebugInfo( TypeError, string( "Media not found: " + sMediaFileName ).c_str() ) ;
		int x = 5; // ERROR!
		return g_sAppDir + "\\Media\\" + sMediaFileName;
	}
}

/*
static string GetWikiPageContents( const string& sPage, const string& sTag, const string& sFile, const long& lLine )
{
	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( GetWikiPageURL( sPage ) ) == false )
	{
		DebugInfo( 
			"(Multiple)", 
			"GetWikiPageContents", 
			"Critical", 
			"Error occurred while trying to download web page.\nError: " + Webpage.GetError() + "\nApplication is aborting.",
			sFile, lLine );
		return string("");
	}

	return GetTaggedText( Webpage.GetContents(), sTag );
}
*/

#endif // UTIL_H