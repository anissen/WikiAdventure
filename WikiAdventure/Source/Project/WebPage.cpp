
#include "WebPage.h"

CWebPage::CWebPage()
{
	m_hOpen = 0;
	m_hFile	= 0;
	m_sErr  = "";
	m_sContents = "";

}

CWebPage::~CWebPage()
{

}

bool CWebPage::DownloadWebPage( const string& sUrl )
{  
	m_sErr = "Initiating";
	DebugInfo( TypeInfo, string("Initiating download. Web page URL is " + GetUntilLast( sUrl, "&action=raw" )).c_str() );
	// Uses the GetUntilLast()-function to remove "&action=raw" from the string, as the XML cannot handle this.

	// Create an Internet connection
	m_hOpen = InternetOpen( "WikiDialog Reader", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );

	if ( !m_hOpen )
	{
		DebugInfo( TypeError, "InternetOpen failed." );
		CleanUp( "InternetOpen failed" );
		return false;
	}

	// Opening the Url and getting a Handle for HTTP file
	m_hFile = InternetOpenUrl( m_hOpen, sUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0 );

	if ( !m_hFile )
	{
		DebugInfo( TypeError, "InternetOpenUrl failed." );
		CleanUp( "InternetOpenUrl failed" );
		return false;
	}

	CHAR buffer[1024];
	DWORD dwRead;
	while ( InternetReadFile( m_hFile, buffer, 1023, &dwRead ) )
	{
		if ( dwRead == 0 )
			break;
		buffer[dwRead] = 0;
		m_sContents += buffer;
	}

	DebugInfo( TypeInfo, "Web page successfully downloaded." );
	CleanUp( "Web page successfully downloaded" );

	return true;
}

void CWebPage::CleanUp( const string& sErr /* = "Unspecified error occurred."  */ )
{
	m_sErr = sErr;

	// clean up
	InternetCloseHandle( m_hFile );
	InternetCloseHandle( m_hOpen );
}

bool CWebPage::DownloadFile( const string& sFileUrl, const string& sSaveToFile, bool bOverwrite )
{
	if ( !bOverwrite )
	{
		if ( PathFileExists( sSaveToFile.c_str() ) )
		{
			DebugInfo( TypeWarning, "A file with the same name already exist." );
			m_sErr = "A file with the same name already exist";
			return true; // No error, just don't download file
		}
	}

	int iResult = URLDownloadToFile( 0, sFileUrl.c_str(), sSaveToFile.c_str(), 0, 0 );
	if ( iResult == 0 )	{
		DebugInfo( TypeInfo, "File successfully downloaded and saved." );
		m_sErr = "File successfully downloaded and saved";
		return true;
	} 
	else {
		DebugInfo( TypeInfo, "Error downloading or saving file." );
		m_sErr = "Error downloading or saving file";
		return false;
	}
}
