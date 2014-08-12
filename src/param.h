///
/// \file	param.h
///	\brief	
///	\date	11 août 2014
/// \author	Nico_user
///
#ifndef PARAM_H_
#define PARAM_H_

/// === INCLUDES	================================================================================
#include <cstdint>

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	11 août 2014
/// \author	Nico_user
class Param
{
public:
	static float Pi;
	static float HalfPi;
	static float TwoPi;

	static uint16_t framerate;
	static uint16_t window_width;
	static uint16_t window_height;
	static uint16_t scale;

	static uint16_t n_fish;
	static uint16_t n_food;

	/// Neural Net
	static float activation_response;
	static float bias;

	/// Fish control
	static float turn_rate_max;

	/// Genetic Algo
	static uint32_t n_ticks;
	static float mutation_rate;
	static float crossover_rate;
	static float perturbation_max;
	static uint16_t n_elite;
	static uint16_t n_copies_elite;

};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// PARAM_H_/// === END OF FILE	================================================================================
