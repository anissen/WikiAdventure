
#ifndef LOCATIONHANDLER_H
#define LOCATIONHANDLER_H

#include "IBaseObject.h"
#include "LocationObject.h"
#include "WikiContent.h"

#include <map>
using std::map;

/** A location object */
class CLocationHandler: public IBaseLoadObject
{
protected:
	CWikiContent*					m_pLocationList;
	map<string, CLocationObject*>	m_mpLocations;
	IBaseLoadObject*				m_pObjectLoading;

public:
	CLocationHandler();
	virtual ~CLocationHandler();

	void LoadContents( const string& sRawLocationData, const string& sGamePage );
	stLoadStatus LoadNext();

	CLocationObject* GetLocation( const string& sLocationName );


	IBaseLoadObject* GetLastLoadedLocation() { return m_pObjectLoading; }
};

#endif // LOCATIONHANDLER_H