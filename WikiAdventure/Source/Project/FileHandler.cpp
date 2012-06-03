
#include "FileHandler.h"
#include "WebPage.h"

#include "../WA-SDL/EngineMain.h"

CFileHandler::CFileHandler()
{
	m_pFileList = 0;
}

CFileHandler::~CFileHandler()
{
	if ( m_pFileList != 0 )
		delete m_pFileList;
	m_pFileList = 0;
}

void CFileHandler::LoadContents( const string& sRawFileData )
{
	m_pFileList = new CWikiContent( sRawFileData, "[[Files:", "]]" );
}

stLoadStatus CFileHandler::LoadNext()
{
	stLoadStatus stReturn;

	stReturn.iNumberLoaded	= m_pFileList->GetCountPopped();
	stReturn.iTotalCount	= m_pFileList->GetCountLoaded();
	stReturn.eObjectLoaded	= FileLoaded;

	if ( m_pFileList->GetCountLeft() == 0 )
	{
		stReturn.sStatus = "Finished!";
		m_bLoadFinished = true;

		if ( m_pFileList != 0 )
			delete m_pFileList;
		m_pFileList = 0;

		return stReturn;
	}

	string sWikiFileName	= GetUntilFirst( m_pFileList->GetTagText(), "|" );
	string sSaveToFileName	= GetAfterFirst( m_pFileList->GetTagText(), "|" );

	// Does the file already exist?
	if ( DoesGameMediaExist( pEngine->GetGameDir(), sSaveToFileName ) == false )
	{
		DownloadFile( sWikiFileName, g_sAppDir+ "\\Media\\" + pEngine->GetGameDir() + "\\" + sSaveToFileName );
	}

	stReturn.sStatus = "File \"" + sWikiFileName + "\" downloaded";

	m_pFileList->Pop();

	return stReturn;
}

void CFileHandler::DownloadFile( const string& sWikiFileName, const string& sSaveToFileName )
{
	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( "http://www.gpwiki.org/index.php/Files:" + sWikiFileName ) == false )
	{
		DebugInfo( TypeError, 
			string( "Error occurred while trying to download web page.\nError: " + Webpage.GetError()).c_str() );
	}

	string sFileUrl = GetTaggedText( Webpage.GetContents(), "<a href=\"", "\"" );

	if ( sFileUrl.length() == 0 )
		DebugInfo( TypeError, "Error extracting the physical file URL." );

	sFileUrl = "http://www.gpwiki.org" + sFileUrl;
	
	Webpage.DownloadFile( sFileUrl, sSaveToFileName );
}

/*
'''<Fonts>'''
* [[Files:Nostalgi.zip|Default.tff]]<br>The main font.
* [[Files:Nostalgi.zip|Dialog.tff]]<br>Dialog font.
'''</Fonts>'''
*/