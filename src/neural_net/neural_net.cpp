///
/// \file
///	\brief
///	\date	11 août 2014
/// \author	Nico_user
///

#include "neural_net.h"

/// === INCLUDES	================================================================================
#include "../utils.h"

/// === NAMESPACES	================================================================================
using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

Neural_Net::Neural_Net()
{
	n_inputs_ = Param::n_inputs;
	n_outputs_ = Param::n_outputs;
	n_layers_ = Param::n_hidden_layers + 1;

	/// Create Network
	if (Param::n_hidden_layers > 0)
	{
		/// Create first hidden layer
		layers_.push_back(Neuron_Layer(Param::n_neurons_per_hidden_layer, n_inputs_));

		for (uint16_t i = 0; i < Param::n_hidden_layers - 1; ++i)
		{
			layers_.push_back(
					Neuron_Layer(Param::n_neurons_per_hidden_layer,
							Param::n_neurons_per_hidden_layer));
		}

		/// Create output layer
		layers_.push_back(Neuron_Layer(n_outputs_, Param::n_neurons_per_hidden_layer));
	}
	else
	{
		/// Create output layer
		layers_.push_back(Neuron_Layer(n_outputs_, n_inputs_));
	}
}

//---------------------------------GetWeights-----------------------------
//
//	returns a vector containing the weights
//
//------------------------------------------------------------------------
vector<float> Neural_Net::getWeights() const
{
	vector<float> weights;

	/// For all layers
	for (uint16_t i = 0; i < layers_.size(); ++i)
	{
		/// for each neuron
		for (uint16_t j = 0; j < layers_[i].neurons_.size(); ++j)
		{
			/// for each weight
			for (uint16_t k = 0; k < layers_[i].neurons_[j].weights_.size(); ++k)
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
void Neural_Net::PutWeights(const vector<float>& weights)
{
	uint16_t weight_cnt = 0;

	/// For all layers
	for (uint16_t i = 0; i < layers_.size(); ++i)
	{
		/// for each neuron
		for (uint16_t j = 0; j < layers_[i].neurons_.size(); ++j)
		{
			/// for each weight
			for (uint16_t k = 0; k < layers_[i].neurons_[j].weights_.size(); ++k)
			{
				layers_[i].neurons_[j].weights_[k] = weights[weight_cnt++];
			}
		}
	}
}

//---------------------------------GetNumberOfWeights---------------------
//
//	returns the total number of weights needed for the net
//
//------------------------------------------------------------------------
uint16_t Neural_Net::GetNumberOfWeights() const
{
	uint16_t weights = 0;

	/// For all layers
	for (auto layer : layers_)
	{
		/// for each neuron
		for (auto neuron : layer.neurons_)
		{
			weights += neuron.weights_.size();
		}
	}

	return weights;
}

//-------------------------------Update-----------------------------------
//
//	given an input vector this function calculates the output vector
//
//------------------------------------------------------------------------
vector<float> Neural_Net::Update(const vector<float>& _inputs)
{
	//stores the resultant outputs from each layer
	vector<float> outputs;
	vector<float> inputs = _inputs;

	//first check that we have the correct amount of inputs
	if (inputs.size() != n_inputs_)
	{
		//just return an empty vector if incorrect.
		cerr << "Incorrect number of input " << __PRETTY_FUNCTION__ << endl;
		return outputs;
	}

	//For each layer...
	for (uint16_t i = 0; i < layers_.size(); ++i)
	{
		if (i > 0)
		{
			inputs = outputs;
		}

		outputs.clear();

		//for each neuron sum the (inputs * corresponding weights).Throw 
		//the total at our sigmoid function to get the output.
		for (auto neuron : layers_[i].neurons_)
		{
			outputs.push_back(neuron.getOutput(inputs));

//			double netinput = 0;
//
//			int NumInputs = layers_[i].neurons_[j].weights_.size();
//
//			//for each weight
//			for (int k = 0; k < NumInputs - 1; ++k)
//			{
//				//sum the weights x inputs
//				netinput += layers_[i].neurons_[j].weights_[k] * inputs[cWeight++];
//			}
//
//			//add in the bias
//			netinput += layers_[i].neurons_[j].weights_[NumInputs - 1] * Param::bias;
//
//			//we can store the outputs from each layer as we generate them.
//			//The combined activation is first filtered through the sigmoid
//			//function
//			outputs.push_back(Sigmoid(netinput, Param::activation_response));
		}
	}

	return outputs;
}

/// === END OF FILES	============================================================================
