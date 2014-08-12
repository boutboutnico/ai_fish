#include "CGenAlg.h"

//-----------------------------------constructor-------------------------
//
//	sets up the population with random floats
//
//-----------------------------------------------------------------------
CGenAlg::CGenAlg(int popsize, float MutRat, float CrossRat, int genome_length) :
		m_iPopSize(popsize),
		m_dMutationRate(MutRat),
		m_dCrossoverRate(CrossRat),
		genome_length_(genome_length),
		m_dTotalFitness(0),
		generation_cnt(0),
		m_iFittestGenome(0),
		m_dBestFitness(0),
		m_dWorstFitness(99999999),
		m_dAverageFitness(0)
{
	//initialise population with chromosomes consisting of random
	//weights and all fitnesses set to zero
	for (int i = 0; i < m_iPopSize; ++i)
	{
		chromosomes_.push_back(SGenome());

		for (int j = 0; j < genome_length_; ++j)
		{
			chromosomes_[i].genes_.push_back(RandomClamped());
		}
	}
}

//---------------------------------Mutate--------------------------------
//
//	mutates a chromosome by perturbing its weights by an amount not 
//	greater than CParams::dMaxPerturbation
//-----------------------------------------------------------------------
void CGenAlg::Mutate(vector<float> &chromo)
{
	//traverse the chromosome and mutate each weight dependent
	//on the mutation rate
	for (uint16_t i = 0; i < chromo.size(); ++i)
	{
		//do we perturb this weight?
		if (RandFloat() < m_dMutationRate)
		{
			//add or subtract a small value to the weight
			chromo[i] += (RandomClamped() * Param::perturbation_max);
		}
	}
}

//----------------------------------GetChromoRoulette()------------------
//
//	returns a chromo based on roulette wheel sampling
//
//-----------------------------------------------------------------------
SGenome CGenAlg::GetChromoRoulette()
{
	//generate a random number between 0 & total fitness count
	float Slice = (float) (RandFloat() * m_dTotalFitness);

	//this will be set to the chosen chromosome
	SGenome TheChosenOne;

	//go through the chromosones adding up the fitness so far
	float FitnessSoFar = 0;

	for (int i = 0; i < m_iPopSize; ++i)
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

//-------------------------------------Crossover()-----------------------
//	
//  given parents and storage for the offspring this method performs
//	crossover according to the GAs crossover rate
//-----------------------------------------------------------------------
void CGenAlg::Crossover(const vector<float> &mum,
						const vector<float> &dad,
						vector<float> &baby1,
						vector<float> &baby2)
{
	//just return parents as offspring dependent on the rate
	//or if parents are the same
	if ((RandFloat() > m_dCrossoverRate) || (mum == dad))
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}

	//determine a crossover point
	int cp = RandInt(0, genome_length_ - 1);

	//create the offspring
	for (int i = 0; i < cp; ++i)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}

	for (uint16_t i = cp; i < mum.size(); ++i)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}

	return;
}

//-----------------------------------Epoch()-----------------------------
//
//	takes a population of chromosones and runs the algorithm through one
//	 cycle.
//	Returns a new population of chromosones.
//
//-----------------------------------------------------------------------
vector<SGenome> CGenAlg::Epoch(vector<SGenome> &old_pop)
{
	generation_cnt++;

	//assign the given population to the classes population
	chromosomes_ = old_pop;

	//reset the appropriate variables
	Reset();

	//sort the population (for scaling and elitism)
	sort(chromosomes_.begin(), chromosomes_.end());

	//calculate best, worst, average and total fitness
	CalculateBestWorstAvTot();

	//create a temporary vector to store new chromosones
	vector<SGenome> vecNewPop;

	//Now to add a little elitism we shall add in some copies of the
	//fittest genomes. Make sure we add an EVEN number or the roulette
	//wheel sampling will crash
	if (!(Param::n_copies_elite * Param::n_elite % 2))
	{
		GrabNBest(Param::n_elite, Param::n_copies_elite, vecNewPop);
	}

	//now we enter the GA loop

	//repeat until a new population is generated
	while (vecNewPop.size() < m_iPopSize)
	{
		//grab two chromosones
		SGenome mum = GetChromoRoulette();
		SGenome dad = GetChromoRoulette();

		//create some offspring via crossover
		vector<float> baby1, baby2;

		Crossover(mum.genes_, dad.genes_, baby1, baby2);

		//now we mutate
		Mutate(baby1);
		Mutate(baby2);

		//now copy into vecNewPop population
		vecNewPop.push_back(SGenome(baby1, 0));
		vecNewPop.push_back(SGenome(baby2, 0));
	}

	//finished so assign new pop back into m_vecPop
	chromosomes_ = vecNewPop;

	return chromosomes_;
}

//-------------------------GrabNBest----------------------------------
//
//	This works like an advanced form of elitism by inserting NumCopies
//  copies of the NBest most fittest genomes into a population vector
//--------------------------------------------------------------------
void CGenAlg::GrabNBest(int NBest, const int NumCopies, vector<SGenome> &Pop)
{
	//add the required amount of copies of the n most fittest
	//to the supplied vector
	while (NBest--)
	{
		for (int i = 0; i < NumCopies; ++i)
		{
			Pop.push_back(chromosomes_[(m_iPopSize - 1) - NBest]);
		}
	}
}

//-----------------------CalculateBestWorstAvTot-----------------------	
//
//	calculates the fittest and weakest genome and the average/total 
//	fitness scores
//---------------------------------------------------------------------
void CGenAlg::CalculateBestWorstAvTot()
{
	m_dTotalFitness = 0;

	float HighestSoFar = 0;
	float LowestSoFar = 9999999;

	for (int i = 0; i < m_iPopSize; ++i)
	{
		//update fittest if necessary
		if (chromosomes_[i].fitness_ > HighestSoFar)
		{
			HighestSoFar = chromosomes_[i].fitness_;

			m_iFittestGenome = i;

			m_dBestFitness = HighestSoFar;
		}

		//update worst if necessary
		if (chromosomes_[i].fitness_ < LowestSoFar)
		{
			LowestSoFar = chromosomes_[i].fitness_;

			m_dWorstFitness = LowestSoFar;
		}

		m_dTotalFitness += chromosomes_[i].fitness_;

	}	//next chromo

	m_dAverageFitness = m_dTotalFitness / m_iPopSize;
}

//-------------------------Reset()------------------------------
//
//	resets all the relevant variables ready for a new generation
//--------------------------------------------------------------
void CGenAlg::Reset()
{
	m_dTotalFitness = 0;
	m_dBestFitness = 0;
	m_dWorstFitness = 9999999;
	m_dAverageFitness = 0;
}

