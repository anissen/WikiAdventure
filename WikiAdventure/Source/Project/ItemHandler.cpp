
#include "ItemHandler.h"

CItemHandler::CItemHandler()
{
	m_pItemList			= 0;
	m_pItemLoading		= 0;
}

CItemHandler::~CItemHandler()
{
	if ( m_pItemList != 0 )
		delete m_pItemList;
	m_pItemList = 0;

	map<string, CItemObject*>::iterator ItemIter = m_mpItems.begin();
	while ( ItemIter != m_mpItems.end() )
	{
		if ( ItemIter->second != 0 )
		{
			DebugInfo( TypeInfo, string("Deleting item with ID \"" + ItemIter->first + "\".").c_str() );
			delete ItemIter->second;
		}

		++ItemIter;
	}
}

void CItemHandler::LoadContents( const string& sRawItemData )
{
	m_pItemList	= new CWikiContent( sRawItemData, "Item" );
}

stLoadStatus CItemHandler::LoadNext()
{
	stLoadStatus stReturn;

	if ( m_pItemLoading != 0 && m_pItemLoading->GetLoadFinished() == false )
	{
		stReturn = m_pItemLoading->LoadNext();

		stReturn.iNumberLoaded	= m_pItemList->GetCountPopped();
		stReturn.iTotalCount	= m_pItemList->GetCountLoaded();

		return stReturn;
	} 
	else if ( m_pItemLoading == 0 || (m_pItemLoading != 0 && m_pItemLoading->GetLoadFinished() == true && m_pItemList->GetCountLeft() > 0) )
	{
		string sItemID = m_pItemList->GetParameter( "Item ID: ", "[No ID]", "<br>" );

		if ( m_mpItems.count( sItemID ) )
		{
			DebugInfo( TypeWarning, string("Item with ID \"" + sItemID + "\" already defined!").c_str() );
			return stReturn;
		}
		else
		{
			// Load the item
			CItemObject* pItem = new CItemObject;
			m_mpItems[ sItemID ] = pItem;
			pItem->LoadContents( m_pItemList->GetTagText() );
			m_pItemLoading = pItem;

			stReturn.sStatus = "Loading item \"" + sItemID + "\"";
			stReturn.eObjectLoaded = ItemLoaded;

			m_pItemList->Pop();

			stReturn.iNumberLoaded	= m_pItemList->GetCountPopped();
			stReturn.iTotalCount	= m_pItemList->GetCountLoaded();
			return stReturn;
		}
	}
	else
	{
		stReturn.iNumberLoaded	= m_pItemList->GetCountPopped();
		stReturn.iTotalCount	= m_pItemList->GetCountLoaded();
		stReturn.sStatus = "Finished!";
		stReturn.eObjectLoaded = ItemLoaded;
		m_bLoadFinished = true;
		return stReturn;
	}



	/*
	stLoadStatus stReturn;

	stReturn.iNumberLoaded	= m_pItemList->GetCountPopped();
	stReturn.iTotalCount	= m_pItemList->GetCountLoaded();

	if ( m_pItemList->GetCountLeft() == 0 )
	{
		stReturn.sStatus = "Finished!";
		stReturn.eObjectLoaded = ItemLoaded;
		m_bLoadFinished = true;
		return stReturn;
	}

	string sItemID = m_pItemList->GetParameter( "Item ID: ", "[No ID]", "<br>" );

	if ( m_mpItems.count( sItemID ) )
	{
		DebugInfo( "CItemHandler", "LoadNext", "Warning", "Item with ID \"" + sItemID + "\" already defined!", FILE_INFO );
	}
	else
	{
		// Load the item
		CItemObject* pItem = new CItemObject;
		m_mpItems[ sItemID ] = pItem;
		pItem->LoadContents( m_pItemList->GetTagText() );
		m_pItemLoading = pItem;

		stReturn.sStatus = "Loading item \"" + sItemID + "\"";
		stReturn.eObjectLoaded = ItemLoaded;
	}

	m_pItemList->Pop();

	return stReturn;
	*/
}

CItemObject* CItemHandler::GetNextItem()
{
	if ( m_LoadIter->second == NULL )
		m_LoadIter = m_mpItems.begin();

	if ( m_LoadIter != m_mpItems.end() ) {
        CItemObject* pReturn = m_LoadIter->second;
		++m_LoadIter;
		return pReturn;
	}

	return 0;
}

void CItemHandler::ResetIteration()
{
	m_LoadIter = m_mpItems.begin();
}

/*
:'''<Item>'''

[data]

:'''</Item>'''
*/