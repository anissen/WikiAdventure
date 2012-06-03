
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "IBaseObject.h"
#include "WikiContent.h"

/** A ? object */
class CFileHandler: public IBaseLoadObject
{
protected:
	CWikiContent* m_pFileList;

public:
	CFileHandler();
	virtual ~CFileHandler();

	void LoadContents( const string& sRawFileData );
	stLoadStatus LoadNext();

	void DownloadFile( const string& sWikiFileName, const string& sSaveToFileName );
};

#endif // FILEHANDLER_H