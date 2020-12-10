#include "Precompiled.h"
#include "LogisticRegression.h"

#include"Datasets.h"

using namespace KWSE::ML;


void KWSE::ML::LogisticRegression::Reset(const float initB0, const float initB1, const float initB2,const float initLearningRate)
{
	b0 = initB0;
	b1 = initB1;
	b2 = initB2;
	learningRate = initLearningRate;
}
float KWSE::ML::LogisticRegression::Fit(const Dataset & dataset)
{
	float truePre = 0.0f;
	float falsePre = 0.0f;
	float _predictb0 = 0.0f;
	float _predictb1 = 0.0f;
	float _predictb2 = 0.0f;
	float totalcost = 0.0f;
	float _m = static_cast<int>(dataset.x0.size());
	for (int i = 0; i < dataset.x0.size(); i++)
	{
		const float x0 = dataset.x0[i];
		const float x1 = dataset.x1[i];
		const float y = dataset.y[i];
		//Cost Function
		const float cost = -(y * log(Predict(x0, x1))) - ((1 - y)*log(1 - Predict(x0, x1)));
		//Gradient Descent
		_predictb0 += (1.0f* (Predict(x0, x1)-y ));
		_predictb1 += (x0*	(Predict(x0, x1)-y )) ;
		_predictb2 += (x1*	(Predict(x0, x1)-y )) ;
		totalcost += cost;
	}
	b0 -= learningRate * _predictb0 / _m;
	b1 -= learningRate * _predictb1 / _m;
	b2 -= learningRate * _predictb2 / _m;
	return totalcost/_m;

}

float KWSE::ML::LogisticRegression::Predict(float x1, float x2) const
{
	float z = b0 + (b1*x1) + (b2*x2);
	float exponential = exp(-z);
	float predict = 1 / (1+ exponential);
	return predict;
}

