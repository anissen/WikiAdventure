
#include "SDLBaseObject.h"

CSDLBaseObject::CSDLBaseObject()
{
	m_pSurface	= 0;
	SetVisible( true );
	SetPos( 0, 0 );
	SetAlpha( 255 );
}


CSDLBaseObject::~CSDLBaseObject()
{

}

void CSDLBaseObject::Think( const int& iElapsedTime )
{

}

void CSDLBaseObject::Render( SDL_Surface *pDestSurface ) {
    if ( ( m_pSurface == 0 ) || ( m_bVisible == false) || ( m_iAlpha == 0 ) ) // If the surface is invalid or it's 100% transparent.
		return;

	SDL_Rect SDestRect;
	SDestRect.x = m_iPosX;  
	SDestRect.y = m_iPosY;
	SDestRect.w = m_pSurface->w;
	SDestRect.h = m_pSurface->h;

	if ( m_iAlpha != 255 ) 
		SDL_SetAlpha( m_pSurface, SDL_SRCALPHA, m_iAlpha );

	SDL_BlitSurface( m_pSurface, &m_pSurface->clip_rect, pDestSurface, &SDestRect );
}

bool CSDLBaseObject::LoadImageFromFile( const string& sFile) {
	if ( m_pSurface != 0 )
		SDL_FreeSurface( m_pSurface );

	SDL_Surface *pTempSurface;
	pTempSurface = IMG_Load( sFile.c_str() );

	if ( pTempSurface == 0 )
	{
		char czError[256];
		sprintf( czError, "Image '%s' could not be opened. Reason: %s", sFile.c_str(), IMG_GetError() );
		DebugInfo( TypeError, czError );
		return false;
	} 
	else 
	{
		if( SDL_SetColorKey( pTempSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB( pTempSurface->format, 255, 0, 255) ) == -1 )
		{
			char czWarning[256];
			sprintf( czWarning, "Image '%s' can't be color keyed. Reason: %s", sFile.c_str(), SDL_GetError() );
			DebugInfo( TypeError, czWarning );
		}
	}

    m_pSurface	= pTempSurface;

	return true;
}

SDL_Rect CSDLBaseObject::GetRect()
{
	SDL_Rect stTemp = { GetPosX(), GetPosY(), GetWidth(), GetHeight() };
	return stTemp;
}
