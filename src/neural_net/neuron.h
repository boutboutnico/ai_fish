///
/// \file	neuron.h
///	\brief	
///	\date	13 août 2014
/// \author	Nico_user
///
#ifndef NEURON_H_
#define NEURON_H_

/// === INCLUDES	================================================================================
#include <cstdint>
#include <vector>

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	13 août 2014
/// \author	Nico_user
class Neuron
{
	friend class Neuron_Layer;
	friend class Neural_Net;

public:
	/// === PUBLIC DECLARATIONS	====================================================================
	Neuron(uint16_t n_inputs);

	float getOutput(const std::vector<float>& inputs);

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// sigmoid response curve
	float sigmoid(float activation, float response);

	/// === PRIVATE ATTRIBUTS	====================================================================

	/// Weights for each input
	std::vector<float> weights_;
};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// NEURON_H_/// === END OF FILE	================================================================================
