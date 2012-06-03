
#ifndef SDLBASEINTERFACE_H
#define SDLBASEINTERFACE_H

#include "SDL.h"

/** A ? object */
class ISDLBaseInterface
{
public:
	ISDLBaseInterface() {};
	virtual ~ISDLBaseInterface() {};

	// Pure virtual functions
	virtual void Think			( const int& iElapsedTime ) = 0;
	virtual void Render			( SDL_Surface* pDestSurface ) = 0;

	// Virtual functions
	virtual void MouseMoved		( const int& iButton, const int& iX, const int& iY ) {};
	virtual void MouseButtonUp	( const int& iButton, const int& iX, const int& iY ) {};
	virtual void MouseButtonDown( const int& iButton, const int& iX, const int& iY ) {};
};

#endif // SDLBASEINTERFACE_H