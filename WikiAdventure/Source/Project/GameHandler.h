
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "GameObject.h"
#include "IBaseObject.h"

#include <vector>
using std::vector;

#include <map>
using std::map;

/** Handles the games */
class CGameHandler: public IBaseLoadObject
{
public:
	struct stGameObjectInfo
	{
		string sName;
		string sDescription;
		string sPage;
	};

protected:
	vector<stGameObjectInfo*> m_vstGames;
	CGameObject* m_pGameObject;

public:
	CGameHandler();
	virtual ~CGameHandler();

	void LoadGameList( const string& sURL );
	void LoadGame( const string& sGamePage );
	void LoadGame( int iGameNum );

	void ClearData();

	void ShowGameList();

	stGameObjectInfo*	GetGameInfo( int iGameNum );
	unsigned int		GetGameCount();

	CGameObject*		GetLoadedGame() { return m_pGameObject; }

	stLoadStatus LoadNext();
};

#endif // GAMEHANDLER_H