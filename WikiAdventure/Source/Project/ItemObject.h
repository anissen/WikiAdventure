
#ifndef ITEMOBJECT_H
#define ITEMOBJECT_H

#include "IBaseObject.h"
#include "Util.h"
#include "ImageHandler.h"

/** A ? object */
class CItemObject: public IBaseLoadObject
{
protected:
	CImageHandler* m_pImageHandler;
	string m_sImage;

	bool   m_bHasImage;
	string m_sDescription;
	string m_sOnLoad;
	string m_sOnClick;

	int m_iPosX;
	int m_iPosY;
	int m_iHeight;
	int m_iWidth;

public:
	CItemObject();
	virtual ~CItemObject();

	bool	GetHasImage()	{ return m_bHasImage; }
	string	GetImageName()	{ return m_sImage; }
	string	GetDescription(){ return m_sDescription; }
	string	GetOnLoad()		{ return m_sOnLoad; }
	string	GetOnClick()	{ return m_sOnClick; }
	int		GetPosX()		{ return m_iPosX; }
	int		GetPosY()		{ return m_iPosY; }
	int		GetWidth()		{ return m_iWidth; }
	int		GetHeight()		{ return m_iHeight; }

	void LoadContents( const string& sRawItemText );
	stLoadStatus LoadNext();
};

#endif // ITEMOBJECT_H