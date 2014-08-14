///
/// \file	hidden_layer.h
///	\brief	Based on http://www.ai-junkie.com/
///			Thanks to Mat Buckland
///	\date	13 août 2014
/// \author	Nico_user
///
#ifndef HIDDEN_LAYER_H_
#define HIDDEN_LAYER_H_

/// === INCLUDES	================================================================================
#include "neuron.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	13 août 2014
/// \author	Nico_user
class Neuron_Layer
{
	friend class Neural_Net;

public:
	/// === PUBLIC DECLARATIONS	====================================================================
	Neuron_Layer(uint16_t n_neurons, uint16_t n_inputs_per_neuron);


private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================

	/// Layer of neurons
	std::vector<Neuron> neurons_;
};

/// === INLINE DEFINITIONS	========================================================================

#endif	/// HIDDEN_LAYER_H_/// === END OF FILE	================================================================================
