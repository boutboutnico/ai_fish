///
/// \file	neuron.cpp
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
///	\date	13 août 2014
/// \author	Nico_user
///

#include "neuron.h"

/// === INCLUDES	================================================================================
#include <math.h>

#include "../utils.h"

/// === NAMESPACES	================================================================================

/// === PUBLIC DEFINITIONS	========================================================================

Neuron::Neuron(uint16_t n_inputs)
{
	/// need an additional weight for the bias
	for (uint16_t i = 0; i < n_inputs + 1; i++)
	{
		//set up the weights with an initial random value
		weights_.push_back(RandomClamped());
	}
}

/// ------------------------------------------------------------------------------------------------
float Neuron::getOutput(const std::vector<float>& inputs)
{
	float result = 0.0;

	/// Check size without taking into account the bias
	if (inputs.size() != weights_.size() - 1)
	{
		cerr << "Incorrect number of input " << __PRETTY_FUNCTION__ << endl;
		return result;
	}

	/// Sum weights without bias
	for (uint16_t i = 0; i < weights_.size() - 1; i++)
	{
		result += weights_[i] * inputs[i];
	}

	/// Add bias
	result += weights_.back() * Param::bias;

	return sigmoid(result, Param::activation_response);
}

/// === PRIVATE DEFINITIONS	========================================================================

float Neuron::sigmoid(float netinput, float response)
{
	return (1 / (1 + exp(-netinput / response)));
}

/// === END OF FILES	============================================================================
