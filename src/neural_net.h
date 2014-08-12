#ifndef CNEURALNET_H
#define CNEURALNET_H
//------------------------------------------------------------------------
//
//	Name: CNeuralNet.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class for creating a feedforward neural net.
//-------------------------------------------------------------------------
#include <vector>
#include <math.h>

#include "utils.h"

//-------------------------------------------------------------------
//	define neuron struct
//-------------------------------------------------------------------
struct Neuron
{
	//the number of inputs into the neuron
	uint16_t n_inputs_;

	//the weights for each input
	std::vector<float> weights_;

	//ctor
	Neuron(uint16_t n_inputs);
};

//---------------------------------------------------------------------
//	struct to hold a layer of neurons.
//---------------------------------------------------------------------

struct NeuronLayer
{
	//the number of neurons in this layer
	uint16_t n_neurons_;

	//the layer of neurons
	std::vector<Neuron> neurons_;

	NeuronLayer(uint16_t n_neurons, uint16_t n_inputs_per_neuron);
};

//----------------------------------------------------------------------
//	neural net class
//----------------------------------------------------------------------

class NeuralNet
{

private:

	uint16_t n_inputs_;

	uint16_t n_outputs_;

	uint16_t n_hidden_layers_;

	uint16_t n_neurons_per_hidden_layer;

	//storage for each layer of neurons including the output layer
	std::vector<NeuronLayer> layers_;

public:

	NeuralNet();

	void CreateNet();

	//gets the weights from the NN
	std::vector<float> GetWeights() const;

	//returns total number of weights in net
	int GetNumberOfWeights() const;

	//replaces the weights with new ones
	void PutWeights(const std::vector<float>& weights);

	//calculates the outputs from a set of inputs
	vector<float> Update(std::vector<float>& inputs);

	//sigmoid response curve
	inline float Sigmoid(float activation, float response);

};

#endif
