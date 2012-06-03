
#include "SDLMultilineTextObject.h"
#include "../Project/Util.h"

CSDLMultilineTextObject::CSDLMultilineTextObject( const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SHoverColor, int iMaxWidth )
{
	// DebugInfo( TypeCreate, "Creating multi-line text object." );

	m_sFont = sFontID;
	m_stColor = SColor;
	m_stHoverColor = SHoverColor;
	m_iMaxWidth = iMaxWidth;
	SetText( sText );
}

CSDLMultilineTextObject::CSDLMultilineTextObject( bool bDoNotSetText, const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SHoverColor, int iMaxWidth )
{
	// DebugInfo( TypeCreate, "Creating multi-line text object." );

	m_sFont = sFontID;
	m_stColor = SColor;
	m_stHoverColor = SHoverColor;
	m_iMaxWidth = iMaxWidth;
}

CSDLMultilineTextObject::~CSDLMultilineTextObject()
{
	DebugInfo( TypeDelete, "Unloading multi-line text object." );
}

void CSDLMultilineTextObject::MouseMoved( const int& iButton, const int& iX, const int& iY )
{
	CSDLHoverObject::MouseMoved( iButton, iX, iY );
}

void CSDLMultilineTextObject::MouseButtonDown( const int& iButton, const int& iX, const int& iY )
{
	CSDLHoverObject::MouseButtonDown( iButton, iX, iY );
}

void CSDLMultilineTextObject::OnMouseEnter()
{
	for ( unsigned int i = 0; i < this->m_vpObjects.size(); ++i )
	{
		try {
			CSDLHoverObject* pHoverObject = static_cast<CSDLBaseTextObject*>( m_vpObjects[i] );
			pHoverObject->SetFocus( true );
			pHoverObject->OnMouseEnter();
		} catch ( ... ) {
		}
	}
}

void CSDLMultilineTextObject::OnMouseLeave()
{
	for ( unsigned int i = 0; i < this->m_vpObjects.size(); ++i )
	{
		try {
			CSDLHoverObject* pHoverObject = static_cast<CSDLBaseTextObject*>( m_vpObjects[i] );
			pHoverObject->SetFocus( false );
			pHoverObject->OnMouseLeave();
		} catch ( ... ) {
		}
	}
}

void CSDLMultilineTextObject::Render( SDL_Surface* pDestSurface )
{
	CSDLHoverObject::Render( pDestSurface );
	CSDLTextSelectionList::Render( pDestSurface );
}

void CSDLMultilineTextObject::SetText( const string& sText )
{
	TTF_Font* pFont = FontHandler.GetFont( m_sFont );

	unsigned int iStartPos	= 0;
	unsigned int iEndPos	= 0;
	int iWidth = 0;

	string sTextString;
	string sTextLine;

	this->Clear();

	vector<string> vTextList = GetSeperatedTextArray( sText, "\n" );
	while ( vTextList.size() > 0 )
	{
		// Get the current line of text
		sTextString = RemoveLeadingSpaces( vTextList.front() );
		sTextLine = sTextString;

		iStartPos = 0;
		iEndPos = sTextString.length();
		while ( true )
		{
			TTF_SizeText( pFont, sTextLine.c_str(), &iWidth, 0 );
			
			// If the text is too wide, shave the last word off
			if ( iWidth > m_iMaxWidth )	
			{
				iEndPos = sTextString.find_last_of( ' ', iEndPos - 1 );

				if ( iEndPos == string::npos )
				{
					AddTextLineObject( sTextString.substr( iStartPos, sTextString.length() - iStartPos ) );
					break;
				}

				sTextLine = sTextString.substr( iStartPos, iEndPos - iStartPos );
			} 
			// If the text is within the width, add the text
			else
			{
				AddTextLineObject( sTextLine.c_str() );
				iStartPos = iEndPos + 1; // The +1 is for removing the leading space in the next line
				iEndPos = sTextString.length();

				if ( iEndPos <= iStartPos )	{
					break;
				}

				sTextLine = sTextString.substr( iStartPos, iEndPos - iStartPos );
			}
		}

		vTextList.erase( vTextList.begin() );
	}
}

void CSDLMultilineTextObject::AddTextLineObject( const string& sText )
{
	// DebugInfo( TypeInfo, "Called from NORMAL!" );
	AddObject( new CSDLBaseTextObject( m_sFont, sText, m_stColor, m_stHoverColor ) );
}

CSDLMultilineDebugTextObject::CSDLMultilineDebugTextObject( const string& sFontID, const string& sText, SDL_Color SColor, SDL_Color SBGColor, SDL_Color SHoverColor, SDL_Color SBGHoverColor, int iMaxWidth ) : CSDLMultilineTextObject( true, sFontID, sText, SColor, SHoverColor, iMaxWidth )
{
	// DebugInfo( TypeCreate, "Creating multi-line DEBUG text object." );
	m_stBGColor = SBGColor;
	m_stBGHoverColor = SBGHoverColor;
	SetText( sText );
}

CSDLMultilineDebugTextObject::~CSDLMultilineDebugTextObject()
{
	// DebugInfo( TypeDelete, "Unloading multi-line DEBUG text object." );
}

void CSDLMultilineDebugTextObject::AddTextLineObject( const string& sText )
{
	// DebugInfo( TypeInfo, "Called from DEBUG!" );
	AddObject( new CSDLDebugTextObject( m_sFont, sText, m_stColor, m_stBGColor, m_stHoverColor, m_stBGHoverColor ) );
}