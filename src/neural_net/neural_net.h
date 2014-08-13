///
/// \file	neuron.h
///	\brief
///	\date	13 août 2014
/// \author	Nico_user
///
#ifndef NEURAL_NET_H_
#define NEURAL_NET_H_

/// === INCLUDES	================================================================================
#include <vector>
#include <math.h>
#include <cstdint>

#include "neuron_layer.h"

/// === NAMESPACE	================================================================================

/// === CLASS	====================================================================================
/// \class
/// \brief
/// \date	13 août 2014
/// \author	Nico_user
class Neural_Net
{

public:
	/// === PUBLIC DECLARATIONS	====================================================================
	Neural_Net();

//	void CreateNet();

//gets the weights from the NN
	std::vector<float> getWeights() const;

	//returns total number of weights in net
	uint16_t GetNumberOfWeights() const;

	//replaces the weights with new ones
	void PutWeights(const std::vector<float>& weights);

	//calculates the outputs from a set of inputs
	std::vector<float> Update(const std::vector<float>& inputs);

private:
	/// === PRIVATE DECLARATIONS	================================================================

	/// === PRIVATE ATTRIBUTS	====================================================================

	/// Number of inputs in Neural Net
	uint16_t n_inputs_;

	/// Number of outputs in Neural Net
	uint16_t n_outputs_;

	/// Number of Hidden Layers in Neural Net with ouput layer
	uint16_t n_layers_;

	/// Hidden Layers and the Output Layer
	std::vector<Neuron_Layer> layers_;

};

#endif
