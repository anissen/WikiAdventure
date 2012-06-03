
#ifndef EXCEPTIONCLASSES_H
#define EXCEPTIONCLASSES_H

#include <string>
using std::string;

class CBaseException
{
protected:
	string m_sDescription;

public:
	CBaseException( const string& sDescription = "[Unspecified exception]" ): m_sDescription( sDescription ) {}
	virtual ~CBaseException() {}

	string GetDescription() { return m_sDescription; }
};

class CWarningException: public CBaseException
{
protected:
	string m_sClassName;
	string m_sFuncName;
	//string m_sFile;
	//long m_lLine;

public:
	CWarningException( 
		const string& sClassName	= "[Unspecified class]", 
		const string& sFuncName		= "[Unspecified function]", 
		const string& sDescription	= "[Unspecified debug information]"	
		): CBaseException( sDescription )
	{
		m_sClassName = sClassName;
		m_sFuncName  = sFuncName;
	}

	virtual ~CWarningException() {}

	string GetInfo()
	{ 
		return m_sClassName + "::" + m_sFuncName + ": " + m_sDescription;
	}
};

#endif // EXCEPTIONCLASSES_H
