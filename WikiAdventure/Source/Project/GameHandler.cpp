
#include "GameHandler.h"
#include "Globals.h"
#include "WebPage.h"

CGameHandler::CGameHandler()
{
	DebugInfo( TypeCreate, "Creating game handle.." );
	m_pGameObject = 0;
}

CGameHandler::~CGameHandler()
{
	DebugInfo( TypeDelete, "Unloading game handler" );
	ClearData();
}

void CGameHandler::ClearData()
{
	DebugInfo( TypeInfo, "Clearing game handler data, removing all allocated resources." );

	if ( m_pGameObject != 0 )
		delete m_pGameObject;
	m_pGameObject = 0;

	while ( m_vstGames.size() > 0 )
	{
		if ( m_vstGames.back() != 0 )
			delete m_vstGames.back();

		m_vstGames.pop_back();
	}
}

void CGameHandler::LoadGameList( const string& sURL )
{
	if ( m_pGameObject != 0 || m_vstGames.size() > 0 ) {
		ClearData();
	}

	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( sURL ) == false )
	{
		DebugInfo( TypeError, 
			string("Error occurred while trying to download web page.\nError: " + Webpage.GetError() + "\nApplication is aborting.").c_str() );
		return;
	}

	string sRawGamesText = GetTaggedText( Webpage.GetContents(), "Games" );
	CWikiContent GameList( sRawGamesText, "[[" + sMainPage + ":", "\n" );

	while ( GameList.GetCountLeft() > 0 )
	{
		stGameObjectInfo* stGameInfo = new stGameObjectInfo;
		GameList.GetInfoFromLink( stGameInfo->sName, stGameInfo->sPage, stGameInfo->sDescription );
		
		m_vstGames.push_back( stGameInfo );
		GameList.Pop();
	}

	/*
	'''<Games>'''
		* [[Community_Projects:WikiAdventure:Games:Test Game|Test Game]]<br>Very short game description here.
		* [[Community_Projects:WikiAdventure:Games:Test Game 2|Another Test Game]]<br>Even shorter game description here.
	'''</Games>'''
	*/
}

CGameHandler::stGameObjectInfo* CGameHandler::GetGameInfo( int iGameNum )
{
	return m_vstGames[ GetGameCount() - iGameNum - 1 ];
}

unsigned int CGameHandler::GetGameCount()
{
	return m_vstGames.size();
}

void CGameHandler::LoadGame( const string& sGamePage )
{
	if ( m_pGameObject != 0 ) {
		delete m_pGameObject;
		m_pGameObject = 0;
	}

	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( GetWikiPageURL( sGamePage ) ) == false )
	{
		DebugInfo( TypeError, 
			string("Error occurred while trying to download web page.\nError: " + Webpage.GetError() + "\nApplication is aborting.").c_str() );
		exit(0);
	}

	m_pGameObject = new CGameObject;
	m_pGameObject->LoadContents( CWikiContent( Webpage.GetContents(), "Game" ), sGamePage );
}

void CGameHandler::LoadGame( int iGameNum )
{
	LoadGame( m_vstGames[iGameNum]->sPage );
}

void CGameHandler::ShowGameList()
{
	/*while ( m_vstGames.size() > 0 )
	{
		cout << "------------" << endl;
		cout << "Game name: " << m_vstGames.back()->sName << endl;
		cout << "Game link: " << m_vstGames.back()->sPage << endl;
		cout << "Game description: " << m_vstGames.back()->sDescription << endl << endl;

		m_vstGames.pop_back();
	}*/
}

stLoadStatus CGameHandler::LoadNext()
{
	if ( m_pGameObject->GetLoadFinished() == true )
	{
		m_bLoadFinished = true;

		stLoadStatus stReturn;
		stReturn.eObjectLoaded = GameLoaded;
		stReturn.iNumberLoaded = 1;
		stReturn.iTotalCount = 1;
		stReturn.sStatus = "Game Finished Loaded";
		return stReturn;
	}

	return m_pGameObject->LoadNext();
}
