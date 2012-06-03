
#ifndef IBASEOBJECT_H
#define IBASEOBJECT_H

#include <string>
using std::string;

enum ObjectLoaded { GameLoaded, LocationLoaded, ItemLoaded, DialogLoaded, ImageLoaded, FontLoaded, FileLoaded };

struct stLoadStatus 
{
	string sStatus;
	ObjectLoaded eObjectLoaded;
	int	iNumberLoaded;
	int iTotalCount;
};

/** A ? object */
class IBaseLoadObject
{
protected:
	bool m_bLoadFinished;
	string m_sWikiSubpage;

public:
	IBaseLoadObject() 
	{ 
		m_bLoadFinished = false; 
	}
	virtual ~IBaseLoadObject() {}

	virtual stLoadStatus LoadNext() = 0;
	bool GetLoadFinished() { return m_bLoadFinished; }
};

#endif // IBASEOBJECT_H