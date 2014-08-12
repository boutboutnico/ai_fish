///
/// \file	engine.h
///	\brief	
///	\date	18 juin 2014
/// \author	Nico_user
///
#ifndef ENGINE_H_
#define ENGINE_H_

/// === INCLUDES	================================================================================
#include <renderer.h>

#include "world.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	18 juin 2014
/// \author	Nico_user

class Engine
{
public:
	/// === PUBLIC DECLARATIONS	====================================================================

	Engine(sdl::Renderer& renderer);

	void update();

	void display(sdl::Renderer& renderer);

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================
	World world_;
};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// ENGINE_H_/// === END OF FILE	================================================================================
