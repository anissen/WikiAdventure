
#ifndef LUASCRIPTHANDLER_H
#define LUASCRIPTHANDLER_H

#include "Globals.h"

#include "LuaPlus.h"
using namespace LuaPlus;

/** Wraps Lua scripting functionality. */
class CLuaScriptHandler
{
private:
	LuaStateOwner m_oLuaState;

public:
	/** An enumeration of the possible results of DoLuaScript() and DoLuaFile(). Can be translated into text using GetResult(). */
	enum ScriptResults { eSuccess = 1, eFileError = 2, eSyntaxError = 3, eMemoryError = 4, eError = 5 };

public:
	/** Default constructor. */
	CLuaScriptHandler();
	/** Destructor. */
	virtual ~CLuaScriptHandler();

	/** Executes a Lua script string.
		@param	sScript Script string.
		@return	The result as an enum. Can be translated with GetResult().
	*/
	ScriptResults DoLuaScript( const string& sScript );

	/** Executes a Lua script file.
		@param	sFile File path.
		@return	The result as an enum. Can be translated with GetResult().
	*/
	ScriptResults DoLuaFile  ( const string& sFile );

	/** Translates a result enumeration into an text description.
		@param	eResult Result enumeration.
		@return	A text description of the result.
	*/
	string GetResult( ScriptResults eResult );

	/** Dumps the content of the Lua state to a file.
	@param	sFile The filename of the dump file
	*/
	void DumpToFile( const string& sFile );
};

#endif // LUASCRIPTHANDLER_H