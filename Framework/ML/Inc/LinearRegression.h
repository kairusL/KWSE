#pragma once
namespace KWSE::ML
{
	struct Dataset;

	class LinearRegression
	{
	public:
		float Fit(const Dataset& dataset);
		float Predict(float X) const;

		void Reset(const float initB0 = 0.0f,const float initB1 = 0.0f,const float initLearningRate = 0.01f);
		float b0 = 0.0f;
		float b1 = 0.0f;
		float learningRate = 0.01f;


	};

}

