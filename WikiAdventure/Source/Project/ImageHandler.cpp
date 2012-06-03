
#include "ImageHandler.h"
#include "WebPage.h"

#include "../WA-SDL/EngineMain.h"

CImageHandler::CImageHandler()
{
	m_pImageList = 0;
}

CImageHandler::~CImageHandler()
{
	if ( m_pImageList != 0 )
		delete m_pImageList;
	m_pImageList = 0;
}

void CImageHandler::LoadContents( const string& sRawImageData )
{
	m_pImageList = new CWikiContent( sRawImageData, "[[Image:", "]]" );
}

stLoadStatus CImageHandler::LoadNext()
{
	stLoadStatus stReturn;

	stReturn.iNumberLoaded	= m_pImageList->GetCountPopped();
	stReturn.iTotalCount	= m_pImageList->GetCountLoaded();
	stReturn.eObjectLoaded = ImageLoaded;

	if ( m_pImageList->GetCountLeft() == 0 )
	{
		stReturn.sStatus = "Finished!";
		m_bLoadFinished = true;

		if ( m_pImageList != 0 )
			delete m_pImageList;
		m_pImageList = 0;

		return stReturn;
	}

	string sWikiFileName	= GetUntilFirst( m_pImageList->GetTagText(), "|" );
	string sSaveToFileName	= GetAfterLast ( m_pImageList->GetTagText(), "|" );
	
	// Does the image already exist?
	if ( DoesGameMediaExist( pEngine->GetGameDir(), sSaveToFileName ) == false )
	{
		DownloadImage( sWikiFileName, g_sAppDir+ "\\Media\\" + pEngine->GetGameDir() + "\\" + sSaveToFileName );
	}

	m_sLastImage = sSaveToFileName;

	stReturn.sStatus = "Image \"" + sWikiFileName + "\" downloaded";

	m_pImageList->Pop();

	return stReturn;
}

void CImageHandler::DownloadImage( const string& sWikiFileName, const string& sSaveToFileName )
{
	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( "http://www.gpwiki.org/index.php/Image:" + sWikiFileName ) == false )
	{
		DebugInfo( TypeError, 
			string("Error occurred while trying to download web page.\nError: " + Webpage.GetError()).c_str() );
	}

	string sImageUrl = GetTaggedText( Webpage.GetContents(), "<img src=\"", "\"" );

	if ( sImageUrl.length() == 0 )
		DebugInfo( TypeError, "Error extracting the physical image URL." );

	sImageUrl = "http://www.gpwiki.org" + sImageUrl;
	
	Webpage.DownloadFile( sImageUrl, sSaveToFileName );
}

/*
'''<Images>'''
[[Image:3dsexample2.jpg|thumb|left|Loading.jpg]]
[[Image:3dtex-example1.jpg|thumb|left|Background.jpg]]
'''</Images>'''
*/