#include "Precompiled.h"
#include "LinearRegression.h"

#include"Datasets.h"

using namespace KWSE::ML;


void KWSE::ML::LinearRegression::Reset(const float initB0, const float initB1, const float initLearningRate)
{
	b0 = initB0;
	b1 = initB1;
	learningRate = initLearningRate;

}
float KWSE::ML::LinearRegression::Fit(const Dataset & dataset)
{
	float _predictb0 = 0.0f;
	float _predictb1 = 0.0f;
	float _mse = 0.0f;
	float _averageError =0.0f;
	float _m = static_cast<int>(dataset.x0.size());

	for (int i = 0; i < dataset.x0.size(); ++i)
	{
		float _prediction = Predict(dataset.x0[i]);
		float _error = _prediction- dataset.y[i];
		_predictb0 += _error;
		_predictb1 += _error* dataset.x0[i];
		_mse += Math::Sqr( _error);
	}
		_predictb0 /= _m;
		_predictb1 /= _m;

		b0 -= learningRate * _predictb0;
		b1 -= learningRate * _predictb1;
		_averageError = _mse / _m  ;


	return _averageError;

}

float KWSE::ML::LinearRegression::Predict(float X) const
{
	return b0+ (b1*X);
}
