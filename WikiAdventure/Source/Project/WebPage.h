
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "Globals.h"

#include <windows.h>
#include <wininet.h>

#include <UrlMon.h>		// For file download
#include "Shlwapi.h"	// For the PathFileExists function

#include "Util.h"

/** Internet and web page functionality. */
class CWebPage  
{
private:
	HINTERNET	m_hOpen;
	HINTERNET	m_hFile;

	string		m_sErr;
	string		m_sContents;

	/** Cleans up the resources allocated for web page download.
		@param sErr String to specify why the function is called.
	*/
	void	CleanUp			( const string& sErr = "Unspecified error occurred." );

public:
	CWebPage();
	virtual ~CWebPage();

	/** Downloads the source code of a web page. The downloaded contents can be retrieved using GetContents().
		@param	sUrl Complete URL to the web page.
		@return A boolean value based on success.
	*/
	bool	DownloadWebPage	( const string& sUrl );

	/** Downloads an internet based file to a local destination.
		@param	sFileUrl Complete URL of the file.
		@param	sSaveToFile The destination of the file. Must point to a valid directory or the function will fail.
		@param	bOverwrite Boolean value specifying whether already existing file at the destination should be overwritten or not.
		@return A boolean value based on success.
	*/
	bool	DownloadFile	( const string& sFileUrl, const string& sSaveToFile, bool bOverwrite = false );

	/** Get the last status message.
		@return String describing the last status message. 
	*/
	string	GetError		() { return m_sErr; }

	/** Get the web page source downloaded last.
	@return String containing web page source.
	*/
	string	GetContents		() { return m_sContents; }
};

#endif // WEBPAGE_H