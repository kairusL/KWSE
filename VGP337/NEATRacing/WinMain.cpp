#include "Car.h"
#include "Track.h"
#include <ML.h>
#include <XEngine.h>

Track track;
std::vector<Car> cars;
std::unique_ptr<ML::NEAT::Population> population;
size_t activeCarCount = 0;

bool Init(float deltaTime);
bool Title(float deltaTime);
bool Play(float deltaTime);
bool EditTrack(float deltaTime);
bool RunNEAT(float deltaTime);

std::function<bool(float)> Tick = Init;

bool Init(float deltaTime)
{
	Tick = Title;
	track.Load();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

bool Title(float deltaTime)
{
	X::DrawScreenText(
		"Hit [Up/Down/Left/Right] to Start\n"
		"Hit [E] to Edit Track\n"
		"Hit [N] to Neat Racing\n"
		"Hit [ESC] to Quit",
		10.0f, 10.0f, 20.0f, X::Colors::White);

	if (X::IsKeyPressed(X::Keys::UP) || 
		X::IsKeyPressed(X::Keys::DOWN) || 
		X::IsKeyPressed(X::Keys::LEFT) || 
		X::IsKeyPressed(X::Keys::RIGHT))
	{
		auto& car = cars.emplace_back();
		car.Load();
		car.Spawn(track.GetStartPosition(), track.GetStartDirection());

		Tick = Play;
	}
	else if (X::IsKeyPressed(X::Keys::E))
	{
		Tick = EditTrack;
	}
	else if (X::IsKeyPressed(X::Keys::N))
	{
		population = std::make_unique<ML::NEAT::Population>(5, 4);

		ML::NEAT::MutationConfig& mutationConfig = population->mutationConfig;
		mutationConfig.connection_mutate_chance = 0.65;
		mutationConfig.perturb_chance = 0.9;
		mutationConfig.crossover_chance = 0.75;
		mutationConfig.link_mutation_chance = 0.85;
		mutationConfig.node_mutation_chance = 0.5;
		mutationConfig.bias_mutation_chance = 0.2;
		mutationConfig.step_size = 0.1;
		mutationConfig.disable_mutation_chance = 0.2;
		mutationConfig.enable_mutation_chance = 0.2;

		for (auto& s : population->species)
		{
			for (auto& g : s.genomes)
			{
				auto& car = cars.emplace_back();
				car.Load();
				car.Spawn(track.GetStartPosition(), track.GetStartDirection());
		
				car.brain = std::make_unique<ML::NEAT::NeuralNet>();
				car.brain->Initialize(g, population->neuralNetConfig);
				car.nextCheckPointIndex = 1;
				car.fitness = 0.0f;
		
				++activeCarCount;
			}
		}

		Tick = RunNEAT;
	}

	track.Render();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

bool Play(float deltaTime)
{
	for (auto& car : cars)
		car.Update(deltaTime, track);

	if (X::IsKeyDown(X::Keys::UP))
		cars[0].Accelerate();
	if (X::IsKeyDown(X::Keys::DOWN))
		cars[0].Brake();
	if (X::IsKeyDown(X::Keys::RIGHT))
		cars[0].Turn(0.05f);
	if (X::IsKeyDown(X::Keys::LEFT))
		cars[0].Turn(-0.05f);

	for (auto& car : cars)
		car.Render();
	track.Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

bool EditTrack(float deltaTime)
{
	track.RunEditor();
	track.Render();

	if (X::IsKeyPressed(X::Keys::ESCAPE))
		Tick = Title;

	return false;
}

bool RunNEAT(float deltaTime)
{
	if (activeCarCount == 0)
	{
		// Feed car fitness back into the genome
		for (auto& s : population->species)
			for (auto& g : s.genomes)
				g.fitness = cars[activeCarCount++].fitness;
	
		population->NewGeneration();
	
		// Use new species/genomes to respawn cars with new brains
		activeCarCount = 0;
		for (auto& s : population->species)
		{
			for (auto& g : s.genomes)
			{
				auto& car = cars[activeCarCount++];
				car.Spawn(track.GetStartPosition(), track.GetStartDirection());

				car.brain = std::make_unique<ML::NEAT::NeuralNet>();
				car.brain->Initialize(g, population->neuralNetConfig);
				car.nextCheckPointIndex = 1;
				car.fitness = 0.0f;
			}
		}
	}
	
	activeCarCount = 0;
	for (auto& car : cars)
	{
		car.Update(deltaTime, track);
		if (car.IsActive())
			++activeCarCount;
	}

	if (X::IsKeyPressed(X::Keys::K))
	{
		for (auto& car : cars)
		{
			if (car.IsActive())
				car.Kill();
		}
		activeCarCount = 0;
	}
	
	for (auto& car : cars)
		car.Render();
	track.Render();

	std::string txt;
	txt += "Generation: " + std::to_string(population->Generation()) + "\n";
	txt += "Cars Active: " + std::to_string(activeCarCount) + "/" + std::to_string(population->speciatingConfig.population) + "\n";
	txt += "Hit [K] to skip generation";
	X::DrawScreenText(txt.c_str(), 10.0f, 10.0f, 20.0f, X::Colors::White);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

bool GameLoop(float deltaTime)
{
	return Tick(deltaTime);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	X::Run(GameLoop);
	X::Stop();
	return 0;
}