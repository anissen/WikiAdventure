
#include "GameObject.h"
#include <assert.h>

CGameObject::CGameObject()
{
	DebugInfo( TypeCreate, "Creating game." );

	m_pImageHandler		= 0;
	m_pFontHandler		= 0;
	m_pLocationHandler	= 0;
}

CGameObject::~CGameObject()
{
	DebugInfo( TypeDelete, "Unloading game, clearing allocated resources." );
	
	if ( m_pLocationHandler != 0 )
		delete m_pLocationHandler;
	m_pLocationHandler = 0;

	if ( m_pFontHandler != 0 )
		delete m_pFontHandler;
	m_pFontHandler = 0;

	if ( m_pImageHandler != 0 )
		delete m_pImageHandler;
	m_pImageHandler = 0;
}

void CGameObject::LoadContents( CWikiContent& rRawContents, const string& sGamePage )
{
	m_sWikiSubpage = sGamePage;

	m_sAuthors = ReplaceInText( rRawContents.GetParameter( "Author: " ), "<br>", "\n" );
	m_sAgeRating = ReplaceInText( rRawContents.GetParameter( "Age Rating: " ), "<br>", "\n" );
	m_sStartLocation = rRawContents.GetParameter( "StartLocation: " );

	DebugInfo( TypeInfo, "Parsing game images data" );
	string sRawImageText = CWikiContent( rRawContents.GetTagText(), "Images" ).GetTagText();
	m_pImageHandler = new CImageHandler;
	m_pImageHandler->LoadContents( sRawImageText );

	DebugInfo( TypeInfo, "Parsing game fonts data" );
	string sRawFontText = CWikiContent( rRawContents.GetTagText(), "Fonts" ).GetTagText();
	m_pFontHandler = new CFileHandler;
	m_pFontHandler->LoadContents( sRawFontText );

	DebugInfo( TypeInfo, "Parsing game locations data" );
	string sRawLocationText = CWikiContent( rRawContents.GetTagText(), "Locations" ).GetTagText();
	m_pLocationHandler = new CLocationHandler;
	m_pLocationHandler->LoadContents( sRawLocationText, sGamePage );
}

void CGameObject::ShowLocations()
{
	//cout << "Showing game locations: " << endl;
	//cout << "FUNCTION DISABLED!" << endl;
	/*
	map<string, CLocationObject*>::iterator iter = m_mpLocations.begin();
	while ( iter != m_mpLocations.end() )
	{
		cout << "Location ID: " << iter->first << endl;

		++iter;
	}
	*/
}

stLoadStatus CGameObject::LoadNext()
{
	stLoadStatus stReturn;
	
	if ( m_pImageHandler->GetLoadFinished() == false ) {
		return m_pImageHandler->LoadNext();
	}

	if ( m_pFontHandler->GetLoadFinished() == false ) {
		stReturn = m_pFontHandler->LoadNext();
		stReturn.eObjectLoaded = FontLoaded; // Set special file format
		return stReturn;
	}

	if ( m_pLocationHandler->GetLoadFinished() == false ) {
		return m_pLocationHandler->LoadNext();
	}

	//IBaseLoadObject* pCurrentLocation = m_pLocationHandler->GetLastLoadedLocation();

	// If all the locations are loaded
	if ( m_pLocationHandler->GetLoadFinished() == true )
	{
		m_bLoadFinished = true;

		/*
		if ( m_pLocationList != 0 ) {
			delete m_pLocationList;
			m_pLocationList = 0;
		}
		*/

		stReturn.eObjectLoaded	= GameLoaded;
		stReturn.sStatus		= "Finished";
		stReturn.iNumberLoaded	= 1;
		stReturn.iTotalCount	= 1;

		return stReturn;
	}
	/*
	// If a location is not loaded OR if a location is loaded, but has finished - then load the next location
	else if ( pCurrentLocation == 0 || (pCurrentLocation != 0 && pCurrentLocation->GetLoadFinished() == true) )
	{
		cout << "Loading a next location." << endl;
		return m_pLocationHandler->LoadNext();
	}
	// If a location is loaded, but hasn't finished - then have the location load the next stuff
	else
	{
		cout << "Updating the loaded location." << endl;
		return pCurrentLocation->LoadNext();
	}

    // We should NEVER get here!
	assert( 0 && "Error loading the locations!" );
	*/

	// We should NEVER get here!
	return stReturn;
}
