///
/// \file	world.h
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef GENETIC_ALGO_H_
#define GENETIC_ALGO_H_

/// === INCLUDES	================================================================================
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "chromosome.h"
#include "../utils.h"

/// === CLASS	====================================================================================
/// \class
/// \brief
/// \date	11 août 2014
/// \author	Nico_user
class Genetic_Algo
{
public:
	/// === PUBLIC DECLARATIONS	====================================================================

	Genetic_Algo(uint16_t popsize, float MutRat, float CrossRat, uint16_t genome_length);

	//this runs the GA for one generation.
	std::vector<Chromosome> NextGeneration(const std::vector<Chromosome> &old_pop);

	//-------------------accessor methods
	std::vector<Chromosome> getPopulation() const
	{
		return chromosomes_;
	}

	float getAverageFitness() const
	{
		return m_dTotalFitness / n_chromosomes_;
	}

	float getBestFitness() const
	{
		return m_dBestFitness;
	}

	uint16_t getGenerationCount() const
	{
		return generation_cnt;
	}

private:
	/// === PRIVATE DECLARATIONS	================================================================

	void ComputePopulationFitness();

	//use to introduce elitism
	void Elitism(uint16_t n_best, uint16_t n_copies, std::vector<Chromosome>& pop) const;

	Chromosome RouletteWheel() const;

	void Crossover(	const Chromosome& mum,
					const Chromosome& dad,
					Chromosome& baby1,
					Chromosome& baby2);

	void Mutate(Chromosome& chromo);

	/// Rest Fitness values
	void Reset();

	/// === PRIVATE ATTRIBUTS	====================================================================

	/// generation counter
	uint16_t generation_cnt;

	/// entire population of chromosomes
	std::vector<Chromosome> chromosomes_;

	/// size of population
	uint16_t n_chromosomes_;

	/// amount of weights per chromo
	uint16_t genome_length_;

	/// probability that a chromosones bits will mutate. (around 0.05 to 0.3)
	float mutation_rate_;

	/// probability of chromosones crossing over bits (~0.7)
	float crossover_rate_;

	//keeps track of the best genome
	int m_iFittestGenome;

	//best fitness this population
	float m_dBestFitness;

	//worst
	float m_dWorstFitness;

	//total fitness of population
	float m_dTotalFitness;

	//average fitness
	float m_dAverageFitness;

};

#endif

/// === END OF FILE	================================================================================
