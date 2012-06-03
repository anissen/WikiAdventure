
#ifndef SDLTEXTSELECTIONLIST_H
#define SDLTEXTSELECTIONLIST_H

#include "SDLObjectQueueList.h"
#include "SDLBaseTextObject.h"

/** A ? object */
class CSDLTextSelectionList: public CSDLObjectQueueList
{
protected:
	int m_iHeaderEnd;
	int m_iHeight;
	int m_iWidth;

public:
	CSDLTextSelectionList();
	virtual ~CSDLTextSelectionList();

	virtual void AddHeader( CSDLBaseObject* pBaseObject );
	virtual void AddObject( CSDLBaseObject* pBaseObject );

	virtual void MouseMoved( const int& iButton, const int& iX, const int& iY );
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY );

	virtual void Clear();

	virtual int GetHeight() { return m_iHeight; }
	virtual int GetWidth()	{ return m_iWidth; }

	virtual void SetPosX( int iPosX );
	virtual void SetPosY( int iPosY );
};

#endif // SDLTEXTSELECTIONLIST_H