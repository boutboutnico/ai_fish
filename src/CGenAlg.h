#ifndef CGENALG_H
#define CGENALG_H
//------------------------------------------------------------------------
//
//	Name: CGenAlg.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Genetic algorithm class.This is based for manipulating std::vectors 
//  of *real* numbers. Used to adjust the weights in a feedforward neural
//  network.
//
//------------------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "utils.h"
//#include "CParams.h"

using namespace std;

//-----------------------------------------------------------------------
//
//	create a structure to hold each genome
//-----------------------------------------------------------------------
struct SGenome
{
	vector<float> genes_;
	float fitness_;

	SGenome() :
			fitness_(0)
	{
	}

	SGenome(const vector<float>& w, float f) :
			genes_(w), fitness_(f)
	{
	}

	/// overload '<' used for sorting
	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.fitness_ < rhs.fitness_);
	}
};

//-----------------------------------------------------------------------
//
//	the genetic algorithm class
//-----------------------------------------------------------------------
class CGenAlg
{
private:

	//this holds the entire population of chromosomes
	vector<SGenome> chromosomes_;

	//size of population
	uint16_t m_iPopSize;

	//probability that a chromosones bits will mutate.
	//Try figures around 0.05 to 0.3 ish
	float m_dMutationRate;

	//probability of chromosones crossing over bits
	//0.7 is pretty good
	float m_dCrossoverRate;

	//amount of weights per chromo
	int genome_length_;

	//total fitness of population
	float m_dTotalFitness;

	//generation counter
	uint16_t generation_cnt;

	//keeps track of the best genome
	int m_iFittestGenome;

	//best fitness this population
	float m_dBestFitness;

	//worst
	float m_dWorstFitness;

	//average fitness
	float m_dAverageFitness;

	void Crossover(	const vector<float> &mum,
					const vector<float> &dad,
					vector<float> &baby1,
					vector<float> &baby2);

	void Mutate(vector<float> &chromo);

	SGenome GetChromoRoulette();

	//use to introduce elitism
	void GrabNBest(int NBest, const int NumCopies, vector<SGenome> &vecPop);

	void CalculateBestWorstAvTot();

	void Reset();

public:

	CGenAlg(int popsize, float MutRat, float CrossRat, int genome_length);

	//this runs the GA for one generation.
	vector<SGenome> Epoch(vector<SGenome> &old_pop);

	//-------------------accessor methods
	vector<SGenome> getPopulation() const
	{
		return chromosomes_;
	}

	float getAverageFitness() const
	{
		return m_dTotalFitness / m_iPopSize;
	}

	float getBestFitness() const
	{
		return m_dBestFitness;
	}

	uint16_t getGenerationCount() const
	{
		return generation_cnt;
	}

};

#endif

