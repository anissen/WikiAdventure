
#ifndef WIKICONTENT_H
#define WIKICONTENT_H

#include "Globals.h"

/** A ? object */
class CWikiContent
{
protected:
	//string m_sRawText;
	vector<string> m_vsTagList;
	int m_iCount;

public:
	CWikiContent( const string& sRawText, const string& sTag );
	CWikiContent( const string& sRawText, const string& sTag, const string& sTagClose );
	virtual ~CWikiContent();

	void	Pop();

	string	GetTagText();
	string	GetParameter( const string& sParameterName, const string& sDefault = "", const string& sParameterClose = "\n" );
	void	GetInfoFromLink( string& rsLinkID, string& rsPage, string& rsDescription );

	int		GetCountLoaded()	{ return m_iCount; }
	int		GetCountLeft()		{ return m_vsTagList.size(); }
	int		GetCountPopped()	{ return GetCountLoaded() - GetCountLeft(); }
};

#endif // WIKICONTENT_H