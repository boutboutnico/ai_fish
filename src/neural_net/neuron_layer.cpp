///
/// \file	hidden_layer.cpp
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
///	\date	13 août 2014
/// \author	Nico_user
///

#include "neuron_layer.h"

/// === INCLUDES	================================================================================

/// === NAMESPACES	================================================================================

/// === PUBLIC DEFINITIONS	========================================================================
Neuron_Layer::Neuron_Layer(uint16_t n_neurons, uint16_t n_inputs_per_neuron)
{
	/// Add neurons into layer
	for (uint16_t i = 0; i < n_neurons; i++)
	{
		neurons_.push_back(Neuron(n_inputs_per_neuron));
	}
}

/// === PRIVATE DEFINITIONS	========================================================================

/// === END OF FILES	============================================================================
