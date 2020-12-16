//====================================================================================================
// KWSE - Kairus(KWL) Super Engine
// Copyright (c) 2020 Peter Chan. All rights reserved.
//====================================================================================================

#include"Precompiled.h"
#include"GeneticAlgorithm.h"
using namespace KWSE::ML;
using namespace KWSE::Math;
namespace
{

}

// Initialize
//		-> Generate the initial population
//		-> Compute fitness for each chromosome
//		-> while(!done) => ga.advance

// how many answer want to generate per generation
void KWSE::ML::GeneticAlgorithm::Initialize(
	int populationSize, // how many answer are there for each loop
	int chromoLength,   // how to generate the individual answers  // how long is my anwser should be 
	int maxGeneValue,	// how to generate the individual answers  // how big can one gene be .
	float crossoverRate, // probabilities
	float mutationRate, // probabilities
	ComputeFitnessFunc computeFitness,
	ComputeCrossOverMateFunc computeCrossOverMateFunc
	//ComputeCrossOverFunc computeCrossOverFunc,
	//ComputeMateFunc		 computeMateFunc
	)
{
	mComputeFitness = std::move(computeFitness);
	mComputeCrossOverMateFunc = std::move(computeCrossOverMateFunc);
	//mComputeCrossOverFunc = std::move(computeCrossOverFunc);
	//mComputeMateFunc = std::move(computeMateFunc);
	//Reset
	mGeneration = 0;
	mMaxGeneValue = maxGeneValue;
	mCrosssoverRate = crossoverRate; // TODO- pass these in
	mMutationRate = mutationRate;// TODO- pass these in

	// Create initial population
	mPopulation.clear();
	mPopulation.resize(populationSize);// Clear->Resize means empty stuff.
	for (auto& genome :mPopulation)  //each gene has chromosome
	{
		genome.chromosome.reserve(chromoLength);// how long one chromosome going to be 
		for (int i = 0; i < chromoLength; ++i)
		{
			genome.chromosome.push_back(KWSE::Math::Random(0,maxGeneValue));
		}
	}
	EvaluatePopulation();
}

void KWSE::ML::GeneticAlgorithm::Initialize(int populationSize, int chromoLength, int maxGeneValue, float crossoverRate, float mutationRate, GeneratePopulationFunc generatePopulationFunc, ComputeFitnessFunc computeFitness, ComputeCrossOverMateFunc computeCrossOverMateFunc)
{
	mComputeFitness = std::move(computeFitness);
	mComputeCrossOverMateFunc = std::move(computeCrossOverMateFunc);

	//Reset
	mGeneration = 0;
	mMaxGeneValue = maxGeneValue;
	mCrosssoverRate = crossoverRate; 
	mMutationRate = mutationRate;

	// Create initial population
	mPopulation.clear();
	generatePopulationFunc(mPopulation);
	EvaluatePopulation();
}

void KWSE::ML::GeneticAlgorithm::Advance() //Moev on to the next generation.
{
	++mGeneration;

	std::vector<Genome> newPopulation;
	newPopulation.reserve(mPopulation.size());

	// Pick only from the better group
	// Perform Elitise: keep top 10%, mate the rest using top 50%
	const int eliteCount = ((int)mPopulation.size() * 10) / 100; // top 10%
	for (int i = 0; i < eliteCount; ++i)
	{
		newPopulation.push_back(mPopulation[i]);  // push top 10% straight to newPopulation.
	}
	const int mateCount = (int)mPopulation.size() - eliteCount; //rest 90% -> going to mate.
	const int cutoff = (int)mPopulation.size() / 2;  // top 50%
	for (int i = 0; i < mateCount; ++i)
	{
		const auto& parent1 = mPopulation[KWSE::Math::Random(0, cutoff)];
		const auto& parent2 = mPopulation[KWSE::Math::Random(0, cutoff)];
		newPopulation.push_back(Mate(parent1, parent2));
	}
	mPopulation = std::move(newPopulation);
	EvaluatePopulation();
}

void KWSE::ML::GeneticAlgorithm::EvaluatePopulation()
{
	for  (auto& genome :mPopulation)
	{
		genome.fitness = mComputeFitness(genome);
	}
	// Sort population, better fitness will be in front.
	std::sort(mPopulation.begin(), mPopulation.end(), [](const auto& a, const auto&b)
	{
		return a.fitness > b.fitness;
	});
}

	// Cross over take two parents then form a new one
GeneticAlgorithm::Genome GeneticAlgorithm::Mate(const Genome & parent1, const Genome & parent2)
{
	Genome offspring;
	offspring.chromosome.reserve(parent1.chromosome.size());
	
	mComputeCrossOverMateFunc(offspring, parent1, parent2, mCrosssoverRate, mMutationRate, mMaxGeneValue);
	//mComputeCrossOverFunc(offspring, parent1, parent2, mCrosssoverRate);
	//mComputeMateFunc(offspring, mMutationRate, (int)mMaxGeneValue);

	//for (size_t i = 0; i < parent1.chromosome.size(); ++i)
	//{
	//	if (KWSE::Math::RandomFloat()<mMutationRate)
	//	{
	//		offspring.chromosome.push_back(Random(0, mMaxGeneValue));
	//	}
	//	else if (RandomFloat()<mCrosssoverRate)
	//	{
	//		offspring.chromosome.push_back(parent1.chromosome[i]);
	//	}
	//	else 
	//	{
	//		offspring.chromosome.push_back(parent2.chromosome[i]);
	//	}
	//}
	return offspring;
}


