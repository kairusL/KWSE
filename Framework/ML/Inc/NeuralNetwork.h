//====================================================================================================
// KWSE - Kairus(KWL) Super Engine
// Copyright (c) 2020 Peter Chan. All rights reserved.
//====================================================================================================

#pragma once
namespace KWSE::ML
{
	// Forward declare a neuron -> so can define a layer
	// Easy to comprehend - > layer to layer  to layer
	// Layer is really just a factor of neurons
	class Neuron;
	using Layer = std::vector<Neuron>;

	struct Connection
	{
		float weight;
	};

	class Neuron
	{
	public:
		//how many output  neuton needs // remember current index.
		//Neuron(size_t numOutputs, size_t myIndex,  bool isBias);
		Neuron(size_t numOutputs, size_t myIndex);

		void SetOutputValue(float value) { mOutputValue = value; }
		float GetOutputValue() const { return mOutputValue; }

		void FeedForward(const Layer& previousLayer);
		void CalculateOutputGradients(float targetValue);
		void CalculateHiddenGradients(const Layer& nextLayer);
		void UpdateInputWeights(Layer& previousLayer);

	private:
		std::vector<Connection> mOutputWeights; //" W1 ,W2 ...." 
		size_t mMyIndex = 0;
		float mOutputValue = 0.0f;  // Release / generate neuron.  /input layer
		float mGradient = 0.0f;
	};

	class NeuralNetwork
	{
	public:
		NeuralNetwork(const std::vector<size_t>& topology);

		void FeedFoward(const std::vector<float>& inputValues);
		void BackPropagate(const std::vector<float>& targetValues);
		std::vector<float> GetResults() const;

	private:
		// Neural Network is an array of layer -> essentially what does that mean it is a  2D array 
		// Vector of layer - which each of those is a vetor of neurons.
		std::vector<Layer> mLayers;  // --> std::vector<std:: vector<Neuron>> mLayers; 

	};
}
//  topology - > streucture of the neural network
//  array<int>
//    2   ,2  ,3
//     |    |    |
//   ------------> number of Layers
//   |  0   0   0
//   |  0   0   0
//   |             0
//   >  number of Neurons


// Idea of neuron( neuton class)-> concept of a layer(Layer = vector<Neuron>; ) 
// NeutalNetwork -> how many layer in each . -> generate the layer
// Each Neuron has weight(randomized)

// XOR - 2, 2, 1
// Setup training data
// 0, 0 -> 0
// 0, 1 -> 1
// 1, 0 -> 1
// 1, 1 -> 0

// training index: 0, 1, 0, 2, 2, 1, 3, 0, 1, 2 ....

// https://archive.ics.uci.edu/ml/datasets/Optical+Recognition+of+Handwritten+Digits
// 3.08