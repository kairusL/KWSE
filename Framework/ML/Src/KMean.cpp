#include "Precompiled.h"
#include "KMean.h"

#include"Datasets.h"

using namespace KWSE::ML;


float KWSE::ML::KMean::Fit(const Dataset & dataset)
{

	float _averageError = 0.0f;

	return _averageError;

}

float KWSE::ML::KMean::Predict(float X) const
{
	return b0 + (b1*X);
}
