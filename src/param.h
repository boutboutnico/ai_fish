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

	static uint16_t window_width;
	static uint16_t window_height;
	static uint16_t scale;

	static uint16_t n_fish;
	static uint16_t n_food;

	static float activation_response;
	static float bias;

	static float turn_rate_max;

};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// PARAM_H_/// === END OF FILE	================================================================================
