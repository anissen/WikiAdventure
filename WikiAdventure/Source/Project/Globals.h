
#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
using std::string;

static string sMainURL	 = "http://www.gpwiki.org/index.php?title=";
static string sMainPage = "Community_Projects:WikiAdventure:Games";
//static string g_sAppDir;

#include "../WA-SDL/Globals.h"
#include "Util.h"

// Comment out the two define statements below to disable debug logging
/** Logs debug data to the console. */
//#define DEBUG_APP_CONSOLE
/** Logs debug data to a XML file using pDebugLog. */
//#define DEBUG_APP_LOG

// Shorthand macros
/** A shorthand macro for the time of compilation. 
	@par Example: 
	Jun  4 2005 16:03:56 
*/
#define COMPILE_TIMESTAMP __DATE__ " " __TIME__
/** A shorthand macro for the current source file and line. 
	@par Example: 
	"[path]\source\project\globals.h", 16 
*/
#define FILE_INFO __FILE__, __LINE__

#ifdef DEBUG_APP_LOG
	#include "..\\Log\\LogHandler.h"
	extern CDebugLogHandler* pDebugLog;
#endif

#ifdef DEBUG_APP_CONSOLE
	#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;
#endif

/** Function to log debug data.
	Data can be logged to either console if DEBUG_APP_CONSOLE is defined or to a XML log file if DEBUG_APP_LOG is defined.
	@param sClassName	Name of the class from which the function is called.
	@param sFuncName	Name of the function from which the function is called.
	@param sDebugType	The type of debug this is; information, error, warning etc..
	@param tInfo		The debug data.
	@param sFile		The physical path of the file from which the function is called.
	@param lLine		The line on which the function is called.

	@remarks sFile and lLine can be defined using the shorthand macro FILE_INFO.
	@par Example Usage:
	@code
	DebugInfo( "CMainClass", "SomeFunction", "Error", "An error occured because of something", FILE_INFO ); 
	@endcode
*/

	/*
template <typename T>
static void DebugInfo (
					   const string& sClassName,
					   const string& sFuncName, 
					   const string& sDebugType, 
					   const T&      tInfo, 
					   const string& sFile, 
					   const long&   lLine)
{
#ifdef DEBUG_APP_LOG
	if ( pDebugLog != 0 )
		pDebugLog->WriteLog( sClassName, sFuncName, sDebugType, tInfo, GetAfterLast( sFile, "\\" ), lLine );
#endif

#ifdef DEBUG_APP_CONSOLE
	cout << endl << sDebugType << ": " << tInfo << endl;
	cout << sClassName << "::" << sFuncName << " (" << GetAfterLast( sFile, "\\" ) << " line " << lLine << ")" << endl << endl;
#endif
}
*/

static string GetGameListURL()
{
	return sMainURL + sMainPage + "&action=raw";
}

static string GetWikiPageURL( const string& sPage )
{
	return sMainURL + sMainPage + ":" + sPage + "&action=raw";
}

#endif GLOBALS_H