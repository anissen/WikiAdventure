
#include "DialogObject.h"
#include "Globals.h"

CDialogObject::CDialogObject()
{
	//DebugInfo( "CDialogObject", "CDialogObject", "Info", "Creating dialog.", FILE_INFO );
	m_pParent = 0;
}

CDialogObject::~CDialogObject()
{
	//DebugInfo( "CDialogObject", "~CDialogObject", "Info", "Unloading dialog.", FILE_INFO );

	while ( m_vpDialogs.size() > 0 )
	{
		if ( m_vpDialogs.back() != 0 )
			delete m_vpDialogs.back();

		m_vpDialogs.pop_back();
	}
}

void CDialogObject::AddChildDialog( CDialogObject* pDialog )
{
	pDialog->SetParent( this );
	m_vpDialogs.push_back( pDialog );
}

void CDialogObject::LoadContents( const string& sRawItemText )
{
	m_sSpeakerID = GetTaggedText( sRawItemText, "Speaker ID: ", "\n" );

	int		iDepth		= 0;
	int		iOldDepth	= 0;
	string	sRawDialogLine;

	CDialogObject* pCurDialogParent = this;
	CDialogObject* pCurDialogChild  = this;

	vector<string> vsDialogLines = GetTaggedTextArray( sRawItemText, "\n#", "\n" );

	for ( unsigned int i = 0; i < vsDialogLines.size(); ++i )
	{
		iDepth = vsDialogLines[i].find_first_not_of( '#', 0 );
		if ( iDepth == string::npos )
		{
			DebugInfo( TypeError, 
				"An error occurred while searching the dialog tree. Possibly an indenting error." );
		}

		sRawDialogLine = vsDialogLines[i].erase( 0, iDepth );

		if ( iDepth > iOldDepth )
		{
			pCurDialogParent = pCurDialogChild;
		}
		else if ( iDepth < iOldDepth )
		{
			for ( int i = iDepth; i < iOldDepth; ++i )
			{
				pCurDialogParent = pCurDialogParent->GetParent();
			}
		}

		iOldDepth = iDepth;

		pCurDialogChild = new CDialogObject;

		// Get the text until the first "<br>"-tag
		pCurDialogChild->m_sDialogText = RemoveLeadingSpaces( GetUntilFirst( sRawDialogLine, "<br>" ) );

		// If there's no "<br>"-tag, then the dialog is only on one line, and there's no scripts.
		if ( pCurDialogChild->m_sDialogText.length() == 0 )
		{
			// The dialog is the entire text
			pCurDialogChild->m_sDialogText = RemoveLeadingSpaces( sRawDialogLine );
		}
		else
		{
			// There's a "<br>"-tag, which means there is room for scripts. Load them.
			pCurDialogChild->m_sOnLoad  = ReplaceInText( GetTaggedText( sRawDialogLine, "OnLoad" ), "<br>", "\n" );
			pCurDialogChild->m_sOnClick = ReplaceInText( GetTaggedText( sRawDialogLine, "OnClick" ), "<br>", "\n" );
		}

		pCurDialogParent->AddChildDialog( pCurDialogChild );
	}
}

CDialogObject* CDialogObject::GetRootDialog()
{
	CDialogObject* pTemp = this;
	while ( pTemp->GetParent()->GetParent() != 0 )
		pTemp = pTemp->GetParent();

	return pTemp;
}
/*
'''

: Dialog ID: Shop01

: Speaker ID: Shopkeeper John

# ''Hi, can I help you?''
## Yes, I would like to have a look at your wares.
### ''[Show wares]''
## Perhabs, what do you sell here?
### ''I've got everything in modern personal security equipment; amour, weapons, shields, bows, you name it!''
#### Great, let me have a look.
##### ''[Show wares]''
#### Not interested.
##### ''Okay, some other time maybe?"
## Have you got any muscle tasks?
### ''Not that I can think of no. But come by from time to time, I sometimes have some jobs that require more muscle than I can muster.'' <br> '''<OnLoad>''' If Stregth = Weak then HideDialog '''</OnLoad>''' <br> '''<OnAfter>''' Print "All that talk about muscle has made you hungry." '''</OnAfter>'''
#### Okay, will do.
## No, thanks.
:'''
*/

void CDialogObject::ShowDialogText ( bool bExpand )
{
	ShowDialogText( &m_vpDialogs , 0, bExpand );
}

void CDialogObject::ShowDialogText ( vector<CDialogObject*>* vDialogs, int iDepth, bool bExpand )
{
	for ( unsigned int i = 0; i < vDialogs->size(); ++i )
	{
		//cout << "  " << string( iDepth * 2, '-' ) << "#" << i + 1 << ": " << vDialogs->at(i)->m_sDialogText << endl;

		if ( bExpand )
			if ( vDialogs->at(i)->m_vpDialogs.size() > 0 )
				ShowDialogText( &vDialogs->at(i)->m_vpDialogs, iDepth + 1, true );
	}
}

vector<CDialogObject*>* CDialogObject::GetChildren()
{
	return &m_vpDialogs;
}
