
#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "IBaseObject.h"
#include "WikiContent.h"

/** A ? object */
class CImageHandler: public IBaseLoadObject
{
protected:
	CWikiContent*	m_pImageList;
	string			m_sLastImage;

public:
	CImageHandler();
	virtual ~CImageHandler();

	void LoadContents( const string& sRawImageData );
	stLoadStatus LoadNext();

	string GetLastImageName() { return m_sLastImage; }

	void DownloadImage( const string& sWikiFileName, const string& sSaveToFileName );
};

#endif // IMAGEHANDLER_H