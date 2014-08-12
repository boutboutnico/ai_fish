///
/// \file	world.cpp
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///

#include "world.h"

/// === INCLUDES	================================================================================

/// === NAMESPACES	================================================================================
using namespace sdl;

/// === PUBLIC DEFINITIONS	========================================================================
World::World(Renderer& renderer)
{
	for (uint16_t i = 0; i < Param::n_fish; i++)
	{
		fishes_.push_back(new Fish(renderer));
	}
	fish_best_ = fishes_.front();

	for (uint16_t i = 0; i < Param::n_food; i++)
	{
		foods_.push_back(new Food());
	}

}

/// ------------------------------------------------------------------------------------------------
void World::update()
{
	Food* pfood;

	for (auto fi : fishes_)
	{
		fi->update(foods_);

		pfood = foods_.at(fi->getClosestFood());

		if (Vec2DLength(fi->getPosition() - pfood->getPosition())
				< (pfood->getRadius() + fi->getRadius()))
		{
			foods_.erase(foods_.begin() + fi->getClosestFood());
			foods_.push_back(new Food());

			fi->incrementFood();
		}

	}

//	for (uint16_t i = 0; i < foods_.size(); i++)
//	{
//		if (foods_.at(i)->isEaten() == true)
//		{
//			foods_.erase(foods_.begin() + i);
//
//			foods_.push_back(new Food());
//		}
//	}

//	Food* pfood;
//	for (auto fi : fishes_)
//	{
//		for (uint16_t fo = 0; fo < foods_.size(); fo++)
//		{
//			pfood = foods_.at(fo);
//
//			if (Vec2DLength(fi->getPosition() - pfood->getPosition())
//					< (pfood->getRadius() + fi->getRadius()))
//			{
//				foods_.erase(foods_.begin() + fo);
//				foods_.push_back(new Food());
//
//				fi->incrementFood();
//			}
//		}
//	}

/// Highlight best fish
	RGBA rgba =
	{ 0, 0, 0, 255 };

	fish_best_->setRGBA(rgba);

	for (uint16_t i = 0; i < fishes_.size(); i++)
	{
		if (fishes_.at(i)->getFitness() > fish_best_->getFitness())
		{
			fish_best_ = fishes_.at(i);
		}
	}

	rgba =
	{	255,0,0,255};
	fish_best_->setRGBA(rgba);
}

/// ------------------------------------------------------------------------------------------------
void World::display(Renderer& renderer)
{
	for (auto it : foods_)
	{
		it->display(renderer);
	}

	for (auto it : fishes_)
	{
		it->display(renderer);
	}
}

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================
