
#include "ItemObject.h"

CItemObject::CItemObject()
{
	//DebugInfo( "CItemObject", "CItemObject", "Info", "Creating item.", FILE_INFO );
	m_pImageHandler = 0;
	m_bHasImage = false;

	m_iPosX = 222;
	m_iPosY = 333;
	m_iHeight = 44;
	m_iWidth = 55;
}

CItemObject::~CItemObject()
{
	//DebugInfo( "CItemObject", "~CItemObject", "Info", "Unloading item.", FILE_INFO );
	if ( m_pImageHandler != 0 )
		delete m_pImageHandler;
	m_pImageHandler = 0;
}

void CItemObject::LoadContents( const string& sRawItemText )
{
	m_sImage		= GetTaggedText( sRawItemText, "[[Image:",	"]]" );
	
	// Only find and download image if there is one.
	if ( m_sImage.length() > 0 ) {
		m_sImage = "";
		m_bHasImage = true;

		m_pImageHandler = new CImageHandler;
		m_pImageHandler->LoadContents( sRawItemText );
	}

	m_sDescription	= GetTaggedText( sRawItemText, "Description: ", "<br>" );
	m_sOnLoad		= ReplaceInText( GetTaggedText( sRawItemText, "OnLoad" ) , "<br>", "\n" );
	m_sOnClick		= ReplaceInText( GetTaggedText( sRawItemText, "OnClick" ) , "<br>", "\n" );

	string sPos		= GetTaggedText( sRawItemText, "Position: ", "<br>", "456, 345" );
	m_iPosX			= atoi( GetUntilFirst( sPos, "," ).c_str() );
	m_iPosY			= atoi( GetAfterLast ( sPos, "," ).c_str() );

	// We don't have the size property if there's an image present.
	if ( m_bHasImage == false ) 
	{
		string sSize	= GetTaggedText( sRawItemText, "Size: ", "<br>", "123, 234" );
		m_iWidth		= atoi( GetUntilFirst( sSize, "," ).c_str() );
		m_iHeight		= atoi( GetAfterLast ( sSize, "," ).c_str() );
	}

	m_sImage = "Media\\" + m_sImage;
}

stLoadStatus CItemObject::LoadNext()
{
	if ( m_bHasImage == true && m_pImageHandler != 0 && m_pImageHandler->GetLoadFinished() == false ) {
		stLoadStatus stReturn = m_pImageHandler->LoadNext();
		m_sImage = m_pImageHandler->GetLastImageName();
		return stReturn;
	}

	m_bLoadFinished = true;

	stLoadStatus stReturn;
	stReturn.sStatus		= "Finish!";
	stReturn.eObjectLoaded	= ItemLoaded;
	return stReturn;
}

/*
'''<Items>'''
:'''<Item>'''
::Item ID: NiceItem01<br><OnLoad>Print "This item was loaded"</OnLoad>
:<'''
/Item>'''
:'''<Item>'''
:: Item ID: NiceItem02<br><OnExamine>Print "You're looking at this item!"</OnExamine>
:'''</Item>'''
'''</Items>'''
*/