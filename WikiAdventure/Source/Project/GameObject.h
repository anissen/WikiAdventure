
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IBaseObject.h"
#include "ImageHandler.h"
#include "FileHandler.h"
#include "LocationHandler.h"
#include "WikiContent.h"

#include <map>
using std::map;

/** A game object */
class CGameObject: public IBaseLoadObject
{
protected:
	CImageHandler*		m_pImageHandler;
	CFileHandler*		m_pFontHandler;
	CLocationHandler*	m_pLocationHandler;

	string m_sAuthors;
	string m_sAgeRating;
	string m_sStartLocation;

public:
	CGameObject();
	virtual ~CGameObject();

	//void LoadContents( const string& sRawContents, const string& sGamePage );
	void LoadContents( CWikiContent& rRawContents, const string& sGamePage );
	void ShowLocations();

	CLocationHandler* GetLocations() { return m_pLocationHandler; }

	string GetAuthors()			{ return m_sAuthors; }
	string GetAgeRating()		{ return m_sAgeRating; }
	string GetStartLocation()	{ return m_sStartLocation; }

	stLoadStatus LoadNext();
};

#endif // GAMEOBJECT_H