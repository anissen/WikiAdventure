
#include "SDLStateLocation.h"
#include "EngineMain.h"
//#include "../Project/ItemObject.h"

CSDLStateLocation::CSDLStateLocation()
{
	DebugInfo( TypeCreate, "Creating location state." );

	m_iPosX = 100;
	m_iPosY = 190;

	m_pLocationObject = 0;

	SetCallbackContainer( this );

	SDL_Color SRedish = { 255, 100, 100 };
	m_pDescription = new CSDLCenterTextObject( "GameDefault", "", SRedish );
	m_pDescription->SetPos( 400, 560 );

	// - Background image
	// - List of items
	// - List of dialogs
}

void CSDLStateLocation::Load( CLocationObject* pLocation )
{
	m_pLocationObject = pLocation;

	pEngine->SetCurrentLocation( this );
	
	string sBackgroundImage = pLocation->GetBackgroundImage();
	if ( sBackgroundImage.length() > 0 ) {
		m_pBackground = new CSDLBaseObject;
		m_pBackground->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), sBackgroundImage ) );

		// Center the image
		m_pBackground->SetPosX( 400 - (m_pBackground->GetWidth() / 2) );
		m_pBackground->SetPosY( 300 - (m_pBackground->GetHeight() / 2) );
	}

	pLocation->GetItems()->ResetIteration();
	CItemObject* pItemObject = 0;
	for ( unsigned int i = 0; i < pLocation->GetItems()->GetCount(); ++i )
	{
		pItemObject = pLocation->GetItems()->GetNextItem();

		CSDLGameItemObject* pGameItemObject = new CSDLGameItemObject;
		pGameItemObject->SetDescription( pItemObject->GetDescription() );
		pGameItemObject->SetPos( pItemObject->GetPosX(), pItemObject->GetPosY() );
		pGameItemObject->SetOnLoad( pItemObject->GetOnLoad() );
		pGameItemObject->SetOnClick( pItemObject->GetOnClick() );

		if ( pItemObject->GetHasImage() == true ) {
			pGameItemObject->LoadImageFromFile( GetMediaPath( pEngine->GetGameDir(), pItemObject->GetImageName() ) );
		} else {
			pGameItemObject->SetHoverDefaultRect( false );
			
			SDL_Rect stRect;
			stRect.x = pGameItemObject->GetPosX();
			stRect.y = pGameItemObject->GetPosY();
			stRect.w = pItemObject->GetWidth();
			stRect.h = pItemObject->GetHeight();
			pGameItemObject->SetHoverRect( stRect );
		}

		AddObject( pGameItemObject );
		
		pGameItemObject->LoadItem(); // Call the OnLoad-scripting if there is one
	}
}

CSDLStateLocation::~CSDLStateLocation()
{
	DebugInfo( TypeDelete, "Deleting location state." );
}

void CSDLStateLocation::OnEnter( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnEnter( pObject );
	try	{
		CSDLGameItemObject* pHover = static_cast<CSDLGameItemObject*>( pObject );
		if ( pHover->GetFocus() )
			m_pDescription->SetText( pHover->GetDescription() );
	} catch ( ... ) { 
		// Object is not a text object, just ignore it.	
		m_pDescription->SetText( "Not a valid object." );
	}
}

void CSDLStateLocation::OnLeave( CSDLBaseObject* pObject )
{
	CSDLBaseState::OnLeave( pObject );
	if ( m_iObjectsWithFocus == 0 )
		m_pDescription->SetText( "" );
}

void CSDLStateLocation::OnClicked( CSDLBaseObject* pObject, const int& iButton )
{
	// m_pDescription->SetText( "Yeah, you clicked it!" );
	m_pDescription->SetText( "" );
}

void CSDLStateLocation::StartDialog( const string& sDialogID )
{
	CSDLDialogList* pDialogList = new CSDLDialogList;
	pDialogList->Load( GetLocationObject()->GetDialog( sDialogID )->GetChildren()->at( 0 )  );
	pEngine->GetStateHandler()->PushLayer( pDialogList );
}