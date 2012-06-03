
#include "LocationObject.h"

CLocationObject::CLocationObject()
{
	DebugInfo( TypeCreate, "Creating location." );

	m_pImageHandler		= 0;
	m_pItemHandler		= 0;
	m_pDialogHandler	= 0;
}

CLocationObject::~CLocationObject()
{
	DebugInfo( TypeDelete, "Unloading location." );

	if ( m_pImageHandler != 0 )
		delete m_pImageHandler;
	m_pImageHandler = 0;

	if ( m_pDialogHandler != 0 )
		delete m_pDialogHandler;
	m_pDialogHandler = 0;

	if ( m_pItemHandler != 0 )
		delete m_pItemHandler;
	m_pItemHandler = 0;
}

void CLocationObject::LoadContents( const string& sLocationPage )
{
	CWebPage Webpage;
	if ( Webpage.DownloadWebPage( GetWikiPageURL( sLocationPage ) ) == false )
	{
		DebugInfo( TypeError, string("Error occurred while trying to download web page.\nError: " + Webpage.GetError() + "\nApplication is aborting.").c_str() );
		return;
	}

	string sRawLocationContents = GetTaggedText( Webpage.GetContents(), "Location" );
	sRawLocationContents = RemoveFromText( sRawLocationContents, "'''" );
	sRawLocationContents = RemoveFromText( sRawLocationContents, "''" );

    m_pImageHandler = new CImageHandler;
	// Only search until the first '<' to avoid downloading the images to the items as well.
	m_pImageHandler->LoadContents( GetUntilFirst( sRawLocationContents, "<" ) );

	m_pItemHandler = new CItemHandler;
	m_pItemHandler->LoadContents( GetTaggedText( sRawLocationContents, "Items" ) );

	m_pDialogHandler = new CDialogHandler;
	m_pDialogHandler->LoadContents( GetTaggedText( sRawLocationContents, "Dialogs" ) );
}

stLoadStatus CLocationObject::LoadNext()
{
	if ( m_pImageHandler->GetLoadFinished() == false  ) {
		stLoadStatus stReturn = m_pImageHandler->LoadNext();
		m_sBackgroundImage = m_pImageHandler->GetLastImageName();
		return stReturn;
	}
	else if ( m_pItemHandler->GetLoadFinished() == false ) 
	{
		return m_pItemHandler->LoadNext();
	} 
	else if ( m_pDialogHandler->GetLoadFinished() == false ) 
	{
		return m_pDialogHandler->LoadNext();
	} 
	else 
	{
		m_bLoadFinished = true;

		stLoadStatus stReturn;
		stReturn.eObjectLoaded = LocationLoaded;
		stReturn.iNumberLoaded = 99;
		stReturn.iTotalCount = 99;
		stReturn.sStatus = "Location load finished";
		return stReturn;
	}
}

/*
'''''<Location>'''''

'''<Items>'''
:'''<Item>'''

[data]

:'''</Item>'''
'''</Items>'''


'''<Dialogs>'''
:'''<Dialog>'''

[data]

:'''</Dialog>'''
'''</Dialogs>'''

'''''</Location>'''''
*/