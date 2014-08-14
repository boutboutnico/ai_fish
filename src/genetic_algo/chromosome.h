///
/// \file	chromosome.h
///	\brief	
///	\date	14 août 2014
/// \author	Nico_user
///
#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

/// === INCLUDES	================================================================================

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
/// \date	14 août 2014
/// \author	Nico_user
class Chromosome
{
	friend class Genetic_Algo;

public:
	/// === PUBLIC DECLARATIONS	====================================================================

	Chromosome() :
			fitness_(0)
	{
	}

	Chromosome(const std::vector<float>& genes, float fitness) :
			genes_(genes), fitness_(fitness)
	{
	}

	/// overload '<' used for sorting
	friend bool operator<(const Chromosome& lhs, const Chromosome& rhs)
	{
		return (lhs.fitness_ < rhs.fitness_);
	}

	friend bool operator==(const Chromosome& left, const Chromosome& right)
	{
		if (left.genes_ == right.genes_) return true;
		else return false;
	}

	inline std::vector<float> getGenes() const
	{
		return genes_;
	}

	inline float getFitness() const
	{
		return fitness_;
	}

	inline void setFitness(float fitness)
	{
		fitness_ = fitness;
	}

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================

	std::vector<float> genes_;

	float fitness_;
};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// CHROMOSOME_H_/// === END OF FILE	================================================================================
