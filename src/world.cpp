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
World::World(Renderer& renderer) :
		tick_cnt(0)
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

	gen_algo_ = new CGenAlg(Param::n_fish, Param::mutation_rate, Param::crossover_rate,
			fishes_.at(0)->getNWeights());

	/// Get weights from GA and put it in fishes' brain
	for (uint16_t i = 0; i < fishes_.size(); i++)
	{
		fishes_[i]->putWeights(gen_algo_->getPopulation()[i].genes_);
	}
}

/// ------------------------------------------------------------------------------------------------
void World::update()
{
	if (tick_cnt++ <= Param::n_ticks)
	{
		Food* pfood;
		for (auto fi : fishes_)
		{
			fi->update(foods_);

			pfood = foods_.at(fi->getClosestFood());

			if (Vec2DLength(fi->getPosition() - pfood->getPosition())
					< (pfood->getRadius() + fi->getRadius()))
			{
				fi->incrementFood(Param::n_food - foods_.size());

				foods_.erase(foods_.begin() + fi->getClosestFood());
//				foods_.push_back(new Food());

				if (foods_.empty()) cerr << "No more foods" << endl;
			}

		}

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
	else
	{
		/// Resupply food
		for (uint16_t i = foods_.size(); i < Param::n_food; i++)
		{
			foods_.push_back(new Food());
		}

		cout << "Next Generation: " << gen_algo_->getGenerationCount() << endl;

		tick_cnt = 0;

		/// Update chromosomes fitness
		vector<SGenome> pop = gen_algo_->getPopulation();
		for (uint16_t i = 0; i < fishes_.size(); i++)
		{
			pop[i].fitness_ = fishes_.at(i)->getFitness();
		}

		/// Run Genetic Algorithm
		pop = gen_algo_->Epoch(pop);

		/// Update Fishes' brain with new values
		for (uint16_t i = 0; i < fishes_.size(); i++)
		{
			fishes_[i]->putWeights(pop[i].genes_);

			fishes_[i]->reset();
		}

		cout << "Average Fitness: " << gen_algo_->getAverageFitness() << endl;
		cout << "Best Fitness:    " << gen_algo_->getBestFitness() << endl << endl;

	}
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
