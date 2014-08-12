///
/// \file
///	\brief
///	\date	11 août 2014
/// \author	Nico_user
///

#include "neural_net.h"

/// === INCLUDES	================================================================================
#include "utils.h"

/// === NAMESPACES	================================================================================
using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

Neuron::Neuron(uint16_t n_inputs) :
		n_inputs_(n_inputs + 1)
{
	//we need an additional weight for the bias hence the +1
	for (int i = 0; i < n_inputs + 1; ++i)
	{
		//set up the weights with an initial random value
		weights_.push_back(RandomClamped());
	}
}

/// === PUBLIC DEFINITIONS	========================================================================

//-----------------------------------------------------------------------
//	ctor creates a layer of neurons of the required size by calling the 
//	SNeuron ctor the rqd number of times
//-----------------------------------------------------------------------
NeuronLayer::NeuronLayer(uint16_t n_neurons, uint16_t n_inputs_per_neuron) :
		n_neurons_(n_neurons)
{
	for (int i = 0; i < n_neurons; ++i)

		neurons_.push_back(Neuron(n_inputs_per_neuron));
}

/// === PUBLIC DEFINITIONS	========================================================================

//------------------------------default ctor ----------------------------
//
//	creates a ANN based on the default values in params.ini
//-----------------------------------------------------------------------
NeuralNet::NeuralNet()
{
	n_inputs_ = 4;
	n_outputs_ = 2;
	n_hidden_layers_ = 1;
	n_neurons_per_hidden_layer = 6;

	CreateNet();
}

//------------------------------createNet()------------------------------
//
//	this method builds the ANN. The weights are all initially set to 
//	random values -1 < w < 1
//------------------------------------------------------------------------
void NeuralNet::CreateNet()
{
	//create the layers of the network
	if (n_hidden_layers_ > 0)
	{
		//create first hidden layer
		layers_.push_back(NeuronLayer(n_neurons_per_hidden_layer, n_inputs_));

		for (int i = 0; i < n_hidden_layers_ - 1; ++i)
		{

			layers_.push_back(NeuronLayer(n_neurons_per_hidden_layer, n_neurons_per_hidden_layer));
		}

		//create output layer
		layers_.push_back(NeuronLayer(n_outputs_, n_neurons_per_hidden_layer));
	}

	else
	{
		//create output layer
		layers_.push_back(NeuronLayer(n_outputs_, n_inputs_));
	}
}

//---------------------------------GetWeights-----------------------------
//
//	returns a vector containing the weights
//
//------------------------------------------------------------------------
vector<float> NeuralNet::GetWeights() const
{
	//this will hold the weights
	vector<float> weights;

	//for each layer
	for (int i = 0; i < n_hidden_layers_ + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < layers_[i].n_neurons_; ++j)
		{
			//for each weight
			for (int k = 0; k < layers_[i].neurons_[j].n_inputs_; ++k)
			{
				weights.push_back(layers_[i].neurons_[j].weights_[k]);
			}
		}
	}

	return weights;
}

//-----------------------------------PutWeights---------------------------
//
//	given a vector of doubles this function replaces the weights in the NN
//  with the new values
//
//------------------------------------------------------------------------
void NeuralNet::PutWeights(const vector<float>& weights)
{
	int cWeight = 0;

	//for each layer
	for (int i = 0; i < n_hidden_layers_ + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < layers_[i].n_neurons_; ++j)
		{
			//for each weight
			for (int k = 0; k < layers_[i].neurons_[j].n_inputs_; ++k)
			{
				layers_[i].neurons_[j].weights_[k] = weights[cWeight++];
			}
		}
	}

	return;
}

//---------------------------------GetNumberOfWeights---------------------
//
//	returns the total number of weights needed for the net
//
//------------------------------------------------------------------------
int NeuralNet::GetNumberOfWeights() const
{

	int weights = 0;

	//for each layer
	for (int i = 0; i < n_hidden_layers_ + 1; ++i)
	{

		//for each neuron
		for (int j = 0; j < layers_[i].n_neurons_; ++j)
		{
			//for each weight
			for (int k = 0; k < layers_[i].neurons_[j].n_inputs_; ++k)

				weights++;

		}
	}

	return weights;
}

//-------------------------------Update-----------------------------------
//
//	given an input vector this function calculates the output vector
//
//------------------------------------------------------------------------
vector<float> NeuralNet::Update(vector<float> &inputs)
{
	//stores the resultant outputs from each layer
	vector<float> outputs;

	int cWeight = 0;

	//first check that we have the correct amount of inputs
	if (inputs.size() != n_inputs_)
	{
		//just return an empty vector if incorrect.
		return outputs;
	}

	//For each layer...
	for (int i = 0; i < n_hidden_layers_ + 1; ++i)
	{
		if (i > 0)
		{
			inputs = outputs;
		}

		outputs.clear();

		cWeight = 0;

		//for each neuron sum the (inputs * corresponding weights).Throw 
		//the total at our sigmoid function to get the output.
		for (int j = 0; j < layers_[i].n_neurons_; ++j)
		{
			double netinput = 0;

			int NumInputs = layers_[i].neurons_[j].n_inputs_;

			//for each weight
			for (int k = 0; k < NumInputs - 1; ++k)
			{
				//sum the weights x inputs
				netinput += layers_[i].neurons_[j].weights_[k] * inputs[cWeight++];
			}

			//add in the bias
			netinput += layers_[i].neurons_[j].weights_[NumInputs - 1] * Param::bias;

			//we can store the outputs from each layer as we generate them. 
			//The combined activation is first filtered through the sigmoid
			//function
			outputs.push_back(Sigmoid(netinput, Param::activation_response));

			cWeight = 0;
		}
	}

	return outputs;
}

//-------------------------------Sigmoid function-------------------------
//
//------------------------------------------------------------------------
float NeuralNet::Sigmoid(float netinput, float response)
{
	return (1 / (1 + exp(-netinput / response)));
}

