///
/// \file	genetic_algo.cpp
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
///	\date	11 août 2014
/// \author	Nico_user
///

#include "genetic_algo.h"

/// === INCLUDES	================================================================================

/// === NAMESPACES	================================================================================
using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

Genetic_Algo::Genetic_Algo(uint16_t popsize, float MutRat, float CrossRat, uint16_t genome_length) :
		generation_cnt(0), n_chromosomes_(popsize), genome_length_(genome_length),

		mutation_rate_(MutRat),
		crossover_rate_(CrossRat),

		m_iFittestGenome(0),
		m_dBestFitness(0), m_dWorstFitness(99999999), m_dTotalFitness(0), m_dAverageFitness(0)
{
	/// initialise population with chromosomes consisting of random
	/// weights and all fitnesses set to zero
	for (uint16_t i = 0; i < n_chromosomes_; ++i)
	{
		chromosomes_.push_back(Chromosome());

		for (uint16_t j = 0; j < genome_length_; ++j)
		{
			chromosomes_[i].genes_.push_back(RandomClamped());
		}
	}
}

/// ------------------------------------------------------------------------------------------------
vector<Chromosome> Genetic_Algo::NextGeneration(const vector<Chromosome> &old_pop)
{
	generation_cnt++;

	//assign the given population to the classes population
	chromosomes_ = old_pop;

	/// Reset fitness evaluations
	Reset();

	/// sort the population (for scaling and elitism)
	sort(chromosomes_.begin(), chromosomes_.end());

	/// calculate best, worst, average and total fitness
	ComputePopulationFitness();

	/// New chromosomes population
	vector<Chromosome> new_pop;

	//Now to add a little elitism we shall add in some copies of the
	//fittest genomes. Make sure we add an EVEN number or the roulette
	//wheel sampling will crash
	if ((Param::n_copies_elite * Param::n_elite) % 2 == 0)
	{
		Elitism(Param::n_elite, Param::n_copies_elite, new_pop);
	}
	else
	{
		cerr << "Elitism input error" << endl;
	}

	//now we enter the GA loop

	//repeat until a new population is generated
	while (new_pop.size() < n_chromosomes_)
	{
		/// grab two chromosones
		Chromosome mum = RouletteWheel();
		Chromosome dad = RouletteWheel();

		//create some offspring via crossover
		Chromosome baby1, baby2;

		Crossover(mum, dad, baby1, baby2);

		//now we mutate
		Mutate(baby1);
		Mutate(baby2);

		//now copy into vecNewPop population
		new_pop.push_back(baby1);
		new_pop.push_back(baby2);
	}

	//finished so assign new pop back into m_vecPop
	chromosomes_ = new_pop;

	return chromosomes_;
}

/// === PRIVATE DEFINITIONS	========================================================================

void Genetic_Algo::ComputePopulationFitness()
{
	m_dTotalFitness = 0;

	float HighestSoFar = 0;
	float LowestSoFar = 9999999;

	for (uint16_t i = 0; i < chromosomes_.size(); ++i)
	{
		/// update fittest if necessary
		if (chromosomes_[i].fitness_ > HighestSoFar)
		{
			HighestSoFar = chromosomes_[i].fitness_;

			m_iFittestGenome = i;

			m_dBestFitness = HighestSoFar;
		}

		/// update worst if necessary
		if (chromosomes_[i].fitness_ < LowestSoFar)
		{
			LowestSoFar = chromosomes_[i].fitness_;

			m_dWorstFitness = LowestSoFar;
		}

		m_dTotalFitness += chromosomes_[i].fitness_;

	}	//next chromo

	m_dAverageFitness = m_dTotalFitness / chromosomes_.size();
}

/// ------------------------------------------------------------------------------------------------
///	This works like an advanced form of elitism by inserting NumCopies
/// copies of the NBest most fittest genomes into a population vector
void Genetic_Algo::Elitism(uint16_t n_best, uint16_t n_copies, vector<Chromosome>& pop) const
{
	/// TODO : use percent

	/// add the required amount of copies of the n most fittest
	/// to the supplied vector
	while (n_best--)
	{
		for (uint16_t i = 0; i < n_copies; ++i)
		{
			/// Population is sorted from weaker to fittest
			pop.push_back(chromosomes_[(n_chromosomes_ - 1) - n_best]);
		}
	}
}

/// ------------------------------------------------------------------------------------------------
Chromosome Genetic_Algo::RouletteWheel() const
{
	//generate a random number between 0 & total fitness count
	float Slice = (float) (RandFloat() * m_dTotalFitness);

	//this will be set to the chosen chromosome
	Chromosome TheChosenOne;

	//go through the chromosones adding up the fitness so far
	float FitnessSoFar = 0;

	for (int i = 0; i < n_chromosomes_; ++i)
	{
		FitnessSoFar += chromosomes_[i].fitness_;

		//if the fitness so far > random number return the chromo at 
		//this point
		if (FitnessSoFar >= Slice)
		{
			TheChosenOne = chromosomes_[i];
			break;
		}
	}

	return TheChosenOne;
}

/// ------------------------------------------------------------------------------------------------
void Genetic_Algo::Crossover(	const Chromosome& mum,
								const Chromosome& dad,
								Chromosome& baby1,
								Chromosome& baby2)
{
	//just return parents as offspring dependent on the rate
	//or if parents are the same
	if ((RandFloat() > crossover_rate_) || (mum == dad))
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}

	//determine a crossover point
	int cp = RandInt(0, genome_length_ - 1);

	/// create the offspring
	for (uint16_t i = 0; i < cp; ++i)
	{
		baby1.genes_.push_back(mum.genes_[i]);
		baby2.genes_.push_back(dad.genes_[i]);
	}

	for (uint16_t i = cp; i < mum.genes_.size(); ++i)
	{
		baby1.genes_.push_back(dad.genes_[i]);
		baby2.genes_.push_back(mum.genes_[i]);
	}

}

/// ------------------------------------------------------------------------------------------------
void Genetic_Algo::Mutate(Chromosome& chromo)
{
	//traverse the chromosome and mutate each weight dependent on the mutation rate
	for (uint16_t i = 0; i < chromo.genes_.size(); ++i)
	{
		//do we perturb this weight?
		if (RandFloat() < mutation_rate_)
		{
			//add or subtract a small value to the weight
			chromo.genes_[i] += (RandomClamped() * Param::perturbation_max);

			cout << "Mutation" << endl;
		}
	}
}

/// ------------------------------------------------------------------------------------------------
void Genetic_Algo::Reset()
{
	m_dTotalFitness = 0;
	m_dBestFitness = 0;
	m_dWorstFitness = 9999999;
	m_dAverageFitness = 0;
}

/// === END OF FILE	================================================================================
