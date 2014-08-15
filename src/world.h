///
/// \file	world.h
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef WORLD_H_
#define WORLD_H_

/// === INCLUDES	================================================================================
#include <vector>

#include <renderer.h>

#include "fish.h"
#include "food.h"
#include "genetic_algo/genetic_algo.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	11 août 2014
/// \author	Nico_user
class World
{
public:
	/// === PUBLIC DECLARATIONS	====================================================================
	World(sdl::Renderer& renderer);
	virtual ~World();

	void update();
	void display(sdl::Renderer& renderer);

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================
	std::vector<Fish*> fishes_;
	Fish* fish_best_;
	std::vector<Food*> foods_;

	Genetic_Algo* gen_algo_;
	uint32_t tick_cnt;
};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// WORLD_H_/// === END OF FILE	================================================================================
