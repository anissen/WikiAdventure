
#include "WikiContent.h"

CWikiContent::CWikiContent( const string& sRawText, const string& sTag )
{
	m_vsTagList = GetTaggedTextArray( sRawText, sTag );

	m_iCount = m_vsTagList.size();
}

CWikiContent::CWikiContent( const string& sRawText, const string& sTag, const string& sTagClose )
{
	m_vsTagList = GetTaggedTextArray( sRawText, sTag, sTagClose );

	m_iCount = m_vsTagList.size();
}

CWikiContent::~CWikiContent()
{
	while ( m_vsTagList.size() > 0 )
	{
		m_vsTagList.pop_back();
	}
}

void CWikiContent::Pop()
{
	if ( m_vsTagList.size() > 0 ) 
		m_vsTagList.pop_back();
}

string CWikiContent::GetTagText()
{ 
	if ( m_vsTagList.size() == 0 ) {
		DebugInfo( TypeWarning, "Tag list is empty!" );
		return string("");
	}

	return m_vsTagList.back();
}

string CWikiContent::GetParameter( const string& sParameterName, const string& sDefault, const string& sParameterClose )
{ 
	string sTemp = GetTaggedText( GetTagText(), sParameterName, sParameterClose );
	
	if ( sTemp.length() == 0 ) {
		return sDefault;
	} else {
		return sTemp;
	}
}

void CWikiContent::GetInfoFromLink( string& rsLinkID, string& rsPage, string& rsDescription )
{
	string sText = GetTagText();
	if ( sText.length() == 0 )
		return;

	rsLinkID		= GetTaggedText( sText, "|", "]]" );
	rsPage			= GetUntilFirst( sText, "|" );
	rsDescription	= GetAfterFirst( sText, "<br>" );
}