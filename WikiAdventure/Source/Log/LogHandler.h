
#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <fstream>
using std::ofstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "time.h" // For getting the system time

/** Handling writing text to a file.

*/
class CFileOutput
{
private:
	string	m_sFileName;
	
public:
	CFileOutput(const string sFileName): m_sFileName(sFileName) {}
	virtual ~CFileOutput() {}
	
	void ClearFile()
	{
		ofstream outFile(m_sFileName.c_str(), std::ios::out | std::ios::trunc);
		outFile.close();
	}
	
	template <typename T> bool Write(const T& Data)
	{
		try {
			ofstream outFile(m_sFileName.c_str(), std::ios::app); // Set the append flag
			if (!outFile.is_open()) {
				throw std::ios::failure("Couldn't open file");
			}
			
			outFile << Data;
			outFile.close();
			
			return true;
		}
		catch (...) {
			return false;
		}
	}
};

/** Handling writing an XML structure to a file.

*/
class CLogHandler
{
private:
	vector<string>	m_vsTags;
	unsigned int	m_iIndent;

protected:
	CFileOutput*	m_CFile;

public:
	CLogHandler(const string& sFileName)
	{
		m_iIndent = 0;
		m_CFile	= new CFileOutput(sFileName);
		m_CFile->ClearFile();
		m_CFile->Write("<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n");
	}
	
	virtual ~CLogHandler()
	{
		while(m_vsTags.size() > 0) {
			CloseTagTree();
		}
		
		if (m_CFile) 
			delete m_CFile;
		m_CFile = 0;
	}

	void AddTagTree	(const string& TagName)
	{
		m_CFile->Write(string(m_iIndent, '\t') + string("<") + TagName + string(">\n"));
		m_vsTags.push_back(TagName);
		m_iIndent += 1;
	}

	template <typename T> 
	void AddTag(const string& TagName, const T& TagValue)
	{
		m_CFile->Write(string(m_iIndent, '\t') + string("<") + TagName + string(">") );
		m_CFile->Write(TagValue);
		m_CFile->Write(string("</") + TagName + string(">\n"));
	}
	
	void CloseTagTree()
	{
		if (m_vsTags.size() > 0) {
			if (m_iIndent > 0) {
				m_iIndent -= 1;
			}
			m_CFile->Write(string(m_iIndent, '\t') + string("</") + m_vsTags[m_vsTags.size()-1] + string(">\n"));
			m_vsTags.pop_back();
		}
	}
};

/** A more specified implementation of CLogHandler

*/
class CMyLogHandler: public CLogHandler
{
public:
	CMyLogHandler(const string& sFileName): CLogHandler(sFileName)
	{
		this->m_CFile->Write("<?xml-stylesheet type=\"text/xsl\" href=\"stylesheet.xsl\" ?>\n\n");

		this->m_CFile->Write("<!-- WikiDialog Reader Dialog Blocks XML -->\n");
		this->m_CFile->Write("<!-- Created by XMLLogger -->\n\n");
	}

	virtual ~CMyLogHandler()
	{
		CLogHandler::~CLogHandler();
		this->m_CFile->Write("\n<!-- Created by XMLLogger -->");
	}
};

class CDebugLogHandler: public CLogHandler
{
public:
	CDebugLogHandler(const string& sFileName): CLogHandler(sFileName)
	{
		this->m_CFile->Write("<?xml-stylesheet type=\"text/xsl\" href=\"debug-stylesheet.xsl\" ?>\n\n");
		this->m_CFile->Write("<!-- Created by XMLLogger -->\n\n");
	}

	virtual ~CDebugLogHandler()
	{
		CLogHandler::~CLogHandler();
		this->m_CFile->Write("\n<!-- Created by XMLLogger -->");
	}

	template <typename T>
		void WriteLog(const string& sClassName,
		const string& sFuncName, 
		const string& sDebugType, 
		const T&      tInfo, 
		const string& sFile, 
		const long&   lLine)
	{
		time_t systemTime;
		systemTime = time(NULL);
		string sTime = ctime(&systemTime);
		sTime.erase( sTime.length() - 1, 1 ); // Remove the newline character

		this->AddTagTree("LogEntry");
		this->AddTag("ClassName",	sClassName);
		this->AddTag("FuncName",	sFuncName);
		this->AddTag("DebugType",	sDebugType);
		this->AddTag("Timestamp",	sTime);
		this->AddTag("Info",		tInfo);
		this->AddTag("File",		sFile);
		this->AddTag("Line",		lLine);
		this->CloseTagTree();	// LogEntry
	}
};

#endif LOGHANDLER_H