//====================================================================================================
// KWSE - Kairus(KWL) Super Engine
// Copyright (c) 2020 Peter Chan. All rights reserved.
//====================================================================================================

#pragma once
namespace KWSE::ML
{
	class GeneticAlgorithm
	{
	public:
		// Genome - > has chromosomes -> gens
		struct Genome
		{
			std::vector<int> chromosome; // [gene] [gene] [gene].....
			float fitness = 0.0f;
		};

		// pass Genome calculate fitness and return fitness 
		using ComputeFitnessFunc = std::function<float(const Genome&)>;
		using ComputeCrossOverMateFunc = std::function<void(Genome&, const Genome&, const Genome&, const float, const float, const float)>;
		using GeneratePopulationFunc = std::function<void(std::vector<Genome>&)>;
		//using ComputeCrossOverFunc = std::function<void(Genome&, const Genome&, const Genome&, const float)>;
		//using ComputeMateFunc = std::function<void(Genome&, const float, const float)>;

		//  1 . Form a random group of population.
		void Initialize(
			int populationSize,
			int chromoLength,
			int maxGeneValue,
			float crossoverRate,
			float mutationRate,
			ComputeFitnessFunc computeFitness,
			ComputeCrossOverMateFunc computeCrossOverMateFunc
			//ComputeCrossOverFunc computeCrossOverFunc,
			//ComputeMateFunc		 computeMateFunc
		);
		void Initialize(
			int populationSize,
			int chromoLength,
			int maxGeneValue,
			float crossoverRate,
			float mutationRate,
			GeneratePopulationFunc generatePopulationFunc,
			ComputeFitnessFunc computeFitness,
			ComputeCrossOverMateFunc computeCrossOverMateFunc
		);
		//  2 . Would generate a new group of population.
		void Advance();
		// When get the bestGenome, sort, and get the front.
		const Genome& GetBestGenome() const { return mPopulation.front(); };
		int GetGeneration() const { return mGeneration; }

	private:
		void EvaluatePopulation(); // check how good is it.

		Genome Mate(const Genome& parent1, const Genome& parent2);


		// Teach algotithm what fitness means
		// Use this function to check how good something is running.
		ComputeFitnessFunc mComputeFitness;
		ComputeCrossOverMateFunc mComputeCrossOverMateFunc;
		//ComputeCrossOverFunc mComputeCrossOverFunc;
		//ComputeMateFunc 	 mComputeMateFunc;
		std::vector<Genome> mPopulation;
		int mGeneration = 0;
		int mMaxGeneValue = 0;

		// percentages
		float mCrosssoverRate = 0.0f;
		float mMutationRate = 0.0f;
	};

}