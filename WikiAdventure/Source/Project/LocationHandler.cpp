
#include "LocationHandler.h"

CLocationHandler::CLocationHandler()
{
	m_pLocationList		= 0;
	m_pObjectLoading	= 0;
}

CLocationHandler::~CLocationHandler()
{
	if ( m_pLocationList != 0 )
		delete m_pLocationList;
	m_pLocationList = 0;

	map<string, CLocationObject*>::iterator LocationItem = m_mpLocations.begin();
	while ( LocationItem != m_mpLocations.end() )
	{
		if ( LocationItem->second != 0 )
		{
			DebugInfo( TypeInfo, string( "Deleting location with ID \"" + LocationItem->first + "\"." ).c_str() );
			delete LocationItem->second;
		}

		++LocationItem;
	}
}

void CLocationHandler::LoadContents( const string& sRawLocationData, const string& sGamePage )
{
	m_sWikiSubpage = sGamePage;
	m_pLocationList = new CWikiContent( sRawLocationData, sMainPage + ":" + sGamePage + ":", "\n" );
}

stLoadStatus CLocationHandler::LoadNext()
{
	stLoadStatus stReturn;

	if ( m_pObjectLoading != 0 && m_pObjectLoading->GetLoadFinished() == false )
	{
		stReturn = m_pObjectLoading->LoadNext();

		stReturn.iNumberLoaded	= m_pLocationList->GetCountPopped();
		stReturn.iTotalCount	= m_pLocationList->GetCountLoaded();

		return stReturn;
	} 
	else if ( m_pObjectLoading == 0 || (m_pObjectLoading != 0 && m_pObjectLoading->GetLoadFinished() == true && m_pLocationList->GetCountLeft() > 0) )
	{
		string sLocationID;
		string sLocationPage;
		string sLocationDescription;

		m_pLocationList->GetInfoFromLink( sLocationID, sLocationPage, sLocationDescription );

		if ( m_mpLocations.count( sLocationID ) )
		{
			DebugInfo( TypeWarning, ("Location with ID \"" + sLocationID + "\" already defined!").c_str() );
			return stReturn;
		}
		else
		{
			// Load the item
			CLocationObject* pLocation = new CLocationObject;
			m_mpLocations[ sLocationID ] = pLocation;
			pLocation->LoadContents( m_sWikiSubpage + ":" + sLocationPage );
			m_pObjectLoading = pLocation;

			stReturn.sStatus = "Loading location \"" + sLocationID + "\"";
			stReturn.eObjectLoaded = LocationLoaded;

			m_pLocationList->Pop();

			stReturn.iNumberLoaded	= m_pLocationList->GetCountPopped();
			stReturn.iTotalCount	= m_pLocationList->GetCountLoaded();
			return stReturn;
		}
	}
	else
	{
		stReturn.iNumberLoaded	= m_pLocationList->GetCountPopped();
		stReturn.iTotalCount	= m_pLocationList->GetCountLoaded();
		stReturn.sStatus = "Finished!";
		stReturn.eObjectLoaded = LocationLoaded;
		m_bLoadFinished = true;
		return stReturn;
	}
/*
	// If a location is not loaded OR if a location is loaded, but has finished - then load the next location
	if ( m_pObjectLoading == 0 || (m_pObjectLoading != 0 && m_pObjectLoading->GetLoadFinished() == true) )
	{
		cout << "Loading a next location." << endl;
		return m_pLocationHandler->LoadNext();
	}
	// If a location is loaded, but hasn't finished - then have the location load the next stuff
	else
	{
		cout << "Updating the loaded location." << endl;
		return m_pObjectLoading->LoadNext();
	}
	*/

	// We should NEVER get here!
	//assert( 0 && "Error loading the locations!" );

	return stReturn;
}

CLocationObject* CLocationHandler::GetLocation( const string& sLocationName )
{
	if ( m_mpLocations.count( sLocationName ) ) {
		return m_mpLocations[ sLocationName ];
	} else {
		return 0;
	}
}
