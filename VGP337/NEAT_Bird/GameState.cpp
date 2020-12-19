#include"GameState.h"
#include<ImGui/Inc/ImPlot.h>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <ImGui/Inc/ImPlot.h>
#include <ImGui/Src/imgui_internal.h>

#include "Background.h"
#include "Bird.h"
#include "PipeManager.h"

namespace
{

	Background bg;
	PipeManager pm;
	std::vector<Bird> birds;
	std::unique_ptr<ML::NEAT::Population> population;
	size_t activeBirdCount = 0;

	//void Init(float deltaTime);
	//void Title(float deltaTime);
	//void Play(float deltaTime);
	//void RunNEAT(float deltaTime);
	//bool RunXOR(float deltaTime);

	Font mfont;

	//void Init(float deltaTime)
	//{
	//	bg.Load();
	//	Tick = Title;
	//	//return mInputSystem->IsKeyPressed(KeyCode::ESCAPE);
	//}

	//void Title(float deltaTime)
	//{
	//	bg.Render();
	//	mfont.Draw("Hit [Space] to Flap", 10.0f, 10.0f, 20.0f, Colors::White);
	//	mfont.Draw("Hit [N] to Neaty Bird", 10.0f, 30.0f, 20.0f, Colors::White);
	//	mfont.Draw("Hit [X] to XOR Test", 10.0f, 50.0f, 20.0f, Colors::White);
	//
	//	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	//	{
	//		auto& bird = birds.emplace_back();
	//		bird.Load();
	//		bird.Spawn({ 150.0f, 300.0f });
	//
	//		Tick = Play;
	//	}
	//	else if (InputSystem::Get()->IsKeyPressed(KeyCode::N))
	//	{
	//		population = std::make_unique<ML::NEAT::Population>(4, 1);
	//
	//		ML::NEAT::MutationConfig& mutationConfig = population->mutationConfig;
	//		mutationConfig.connection_mutate_chance = 0.65;
	//		mutationConfig.perturb_chance = 0.9;
	//		mutationConfig.crossover_chance = 0.75;
	//		mutationConfig.link_mutation_chance = 0.85;
	//		mutationConfig.node_mutation_chance = 0.5;
	//		mutationConfig.bias_mutation_chance = 0.2;
	//		mutationConfig.step_size = 0.1;
	//		mutationConfig.disable_mutation_chance = 0.2;
	//		mutationConfig.enable_mutation_chance = 0.2;
	//
	//		for (auto& s : population->species)
	//		{
	//			for (auto& g : s.genomes)
	//			{
	//				auto& bird = birds.emplace_back();
	//				bird.Load();
	//				bird.Spawn({ 150.0f, 300.0f });
	//
	//				bird.brain = std::make_unique<ML::NEAT::NeuralNet>();
	//				bird.brain->Initialize(g, population->neuralNetConfig);
	//				bird.fitness = 0.0f;
	//
	//				++activeBirdCount;
	//			}
	//		}
	//
	//		Tick = RunNEAT;
	//	}
	//	else if (InputSystem::Get()->IsKeyPressed(KeyCode::X))
	//	{
	//		Tick = RunXOR;
	//	}
	//
	//	//return mInputSystem->IsKeyPressed(KeyCode::ESCAPE);
	//}

	//void Play(float deltaTime)
	//{
	//	bg.Update(deltaTime);
	//	pm.Update(deltaTime);
	//
	//	for (auto& bird : birds)
	//		bird.Update(deltaTime, pm);
	//
	//	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	//		birds[0].Flap();
	//
	//	bg.Render();
	//	pm.Render();
	//	for (auto& bird : birds)
	//		bird.Render();
	//
	//	//return mInputSystem->IsKeyPressed(KeyCode::ESCAPE);
	//}

	//void RunNEAT(float deltaTime)
	//{
	//	if (activeBirdCount == 0)
	//	{
	//		// Feed bird fitness back into the genome
	//		for (auto& s : population->species)
	//			for (auto& g : s.genomes)
	//				g.fitness = birds[activeBirdCount++].fitness;
	//
	//		population->NewGeneration();
	//
	//		// Use new species/genomes to respawn birds with new brains
	//		activeBirdCount = 0;
	//		for (auto& s : population->species)
	//		{
	//			for (auto& g : s.genomes)
	//			{
	//				auto& bird = birds[activeBirdCount++];
	//				bird.Spawn({ 150.0f, 300.0f });
	//
	//				bird.brain = std::make_unique<ML::NEAT::NeuralNet>();
	//				bird.brain->Initialize(g, population->neuralNetConfig);
	//				bird.fitness = 0.0f;
	//			}
	//		}
	//
	//		pm.Reset();
	//	}
	//
	//	bg.Update(deltaTime);
	//	pm.Update(deltaTime);
	//
	//	activeBirdCount = 0;
	//	for (auto& bird : birds)
	//	{
	//		bird.Update(deltaTime, pm);
	//		if (bird.IsAlive())
	//			++activeBirdCount;
	//	}
	//
	//	if (InputSystem::Get()->IsKeyPressed(KeyCode::K))
	//	{
	//		for (auto& bird : birds)
	//		{
	//			if (bird.IsAlive())
	//				bird.Kill();
	//		}
	//		activeBirdCount = 0;
	//	}
	//
	//	bg.Render();
	//	pm.Render();
	//	for (auto& bird : birds)
	//		bird.Render();
	//
	//	std::string txt;
	//	txt += "Generation: " + std::to_string(population->Generation()) + "\n";
	//	txt += "Birds Alive: " + std::to_string(activeBirdCount) + "/" + std::to_string(population->speciatingConfig.population) + "\n";
	//	txt += "Hit [K] to skip generation";
	//	mfont.Draw(txt.c_str(), 10.0f, 10.0f, 20.0f, Colors::White);
	//
	//	//return mInputSystem->IsKeyPressed(KeyCode::ESCAPE);
	//}

	//bool RunXOR(float deltaTime)
	//{
	//	auto XORTest = [](ML::NEAT::NeuralNet& n, bool log) -> size_t
	//	{
	//		size_t fitness = 0;
	//
	//		std::string message = "     > begin xor test\n        ( ";
	//
	//		auto output = n.Evaluate({ 0.0, 0.0 });
	//		message += std::to_string(output[0]) + " ";
	//		fitness += (size_t)std::min(1.0 / ((0.0 - output[0]) * (0.0f - output[0])), 50.0);
	//
	//		output = n.Evaluate({ 0.0, 1.0 });
	//		message += std::to_string(output[0]) + " ";
	//		fitness += (size_t)std::min(1.0 / ((1.0 - output[0]) * (1.0 - output[0])), 50.0);
	//
	//		output = n.Evaluate({ 1.0, 0.0 });
	//		message += std::to_string(output[0]) + " ";
	//		fitness += (size_t)std::min(1.0 / ((1.0 - output[0]) * (1.0 - output[0])), 50.0);
	//
	//		output = n.Evaluate({ 1.0, 1.0 });
	//		message += std::to_string(output[0]) + " ";
	//		fitness += (size_t)std::min(1.0 / ((0.0 - output[0]) * (0.0 - output[0])), 50.0);
	//
	//		if (log)
	//		{
	//			message += ") fitness = " + std::to_string(fitness);
	//			LOG("%s", message.c_str());
	//		}
	//
	//		return fitness;
	//	};
	//
	//	ML::NEAT::Population p(2, 1);
	//	ML::NEAT::NeuralNet bestGuy;
	//
	//	ML::NEAT::MutationConfig& mutationConfig = p.mutationConfig;
	//	mutationConfig.connection_mutate_chance = 0.65 * 0.5;
	//	mutationConfig.perturb_chance = 0.9;
	//	mutationConfig.crossover_chance = 0.75 * 0.5;
	//	mutationConfig.link_mutation_chance = 0.85 * 0.5;
	//	mutationConfig.node_mutation_chance = 0.5 * 0.5;
	//	mutationConfig.bias_mutation_chance = 0.2 * 0.5;
	//	mutationConfig.step_size = 0.1 * 0.5;
	//	mutationConfig.disable_mutation_chance = 0.2;
	//	mutationConfig.enable_mutation_chance = 0.2 * 0.5;
	//
	//	size_t max_fitness = 0;
	//	while (max_fitness < 200)
	//	{
	//		size_t current_fitness = 0;
	//		size_t min_fitness = 100000;
	//		for (auto& s : p.species)
	//		{
	//			for (auto& g : s.genomes)
	//			{
	//				ML::NEAT::NeuralNet n;
	//				n.Initialize(g, p.neuralNetConfig);
	//				current_fitness = XORTest(n, false);
	//				if (current_fitness < min_fitness)
	//					min_fitness = current_fitness;
	//				if (current_fitness > max_fitness)
	//				{
	//					max_fitness = current_fitness;
	//					bestGuy = n;
	//				}
	//				g.fitness = current_fitness;
	//			}
	//		}
	//
	//		LOG("Generation %zd successfuly tested. Species: %zd, Global min fitness: %zd, Global max fitness: %zd", p.Generation(), p.species.size(), min_fitness, max_fitness);
	//		p.NewGeneration();
	//	}
	//
	//	XORTest(bestGuy, true);
	//	return true;
	//}


}


void GameState::Initialize()
{

	mfont.Initialize();
	//bg.Load();

}
void GameState::Terminate()
{

	mfont.Terminate();
	bg.Terminate();

}
void GameState::Update(float deltaTime)
{
	mDeltaTime = deltaTime;
	switch (mCurrentyState)
	{
	case State::Init:
		Tick = std::bind(&GameState::Init, this, deltaTime);
		break;
	case State::Title:
		Tick = std::bind(&GameState::Title, this, deltaTime);
		break;
	case State::Play:
		Tick = std::bind(&GameState::Play, this, deltaTime);
		break;
	case State::RunNEAT:
		Tick = std::bind(&GameState::RunNEAT, this, deltaTime);
		break;
	case State::RunXOR:
		Tick = std::bind(&GameState::RunXOR, this, deltaTime);
		break;
	default:
		break;
	}
}

void GameState::Render()
{
	//bg.Render();
	//GraphicsSystem::Get()->BeginRender();
	//SpriteRenderer::Get()->BeginRender();
	Tick(mDeltaTime);
	//GraphicsSystem::Get()->EndRender();
	//SpriteRenderer::Get()->EndRender();
}


void  GameState::DebugUI()
{
	//ImGui::SetNextWindowSize({ 800.0f,600.0f });
	//ImGui::Begin("game", nullptr, ImGuiWindowFlags_NoResize);
	//
	//
	//
	//
	//ImGui::End();
}

bool GameState::Init(float deltaTime)
{
	bg.Load();
	//Tick = std::bind(&GameState::Title,this, deltaTime); 
	mCurrentyState = State::Title;
	return InputSystem::Get()->IsKeyPressed(KeyCode::ESCAPE);
}

bool GameState::Title(float deltaTime)
{
	bg.Render();
	mfont.Draw("Hit [Space] to Flap", 10.0f, 10.0f, 20.0f, Colors::Black);
	mfont.Draw("Hit [N] to Neaty Bird", 10.0f, 30.0f, 20.0f, Colors::Black);
	mfont.Draw("Hit [X] to XOR Test", 10.0f, 50.0f, 20.0f, Colors::Black);

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		auto& bird = birds.emplace_back();
		bird.Load();
		bird.Spawn({ 150.0f, 300.0f });

		mCurrentyState = State::Play;
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::N))
	{
		population = std::make_unique<ML::NEAT::Population>(4, 1);

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
				auto& bird = birds.emplace_back();
				bird.Load();
				bird.Spawn({ 150.0f, 300.0f });

				bird.brain = std::make_unique<ML::NEAT::NeuralNet>();
				bird.brain->Initialize(g, population->neuralNetConfig);
				bird.fitness = 0.0f;

				++activeBirdCount;
			}
		}

		mCurrentyState = State::RunNEAT;
	}
	else if (InputSystem::Get()->IsKeyPressed(KeyCode::X))
	{
		mCurrentyState = State::RunXOR;
	}

	return InputSystem::Get()->IsKeyPressed(KeyCode::ESCAPE);
}

bool GameState::Play(float deltaTime)
{
	bg.Update(deltaTime);
	pm.Update(deltaTime);

	for (auto& bird : birds)
		bird.Update(deltaTime, pm);

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
		birds[0].Flap();

	bg.Render();
	pm.Render();
	for (auto& bird : birds)
		bird.Render();

	return InputSystem::Get()->IsKeyPressed(KeyCode::ESCAPE);
}

bool GameState::RunNEAT(float deltaTime)
{
	if (activeBirdCount == 0)
	{
		// Feed bird fitness back into the genome
		for (auto& s : population->species)
			for (auto& g : s.genomes)
				g.fitness = birds[activeBirdCount++].fitness;

		population->NewGeneration();

		// Use new species/genomes to respawn birds with new brains
		activeBirdCount = 0;
		for (auto& s : population->species)
		{
			for (auto& g : s.genomes)
			{
				auto& bird = birds[activeBirdCount++];
				bird.Spawn({ 150.0f, 300.0f });

				bird.brain = std::make_unique<ML::NEAT::NeuralNet>();
				bird.brain->Initialize(g, population->neuralNetConfig);
				bird.fitness = 0.0f;
			}
		}

		pm.Reset();
	}

	bg.Update(deltaTime);
	pm.Update(deltaTime);

	activeBirdCount = 0;
	for (auto& bird : birds)
	{
		bird.Update(deltaTime, pm);
		if (bird.IsAlive())
			++activeBirdCount;
	}

	if (InputSystem::Get()->IsKeyPressed(KeyCode::K))
	{
		for (auto& bird : birds)
		{
			if (bird.IsAlive())
				bird.Kill();
		}
		activeBirdCount = 0;
	}

	bg.Render();
	pm.Render();
	for (auto& bird : birds)
		bird.Render();

	std::string txt;
	txt += "Generation: " + std::to_string(population->Generation()) + "\n";
	txt += "Birds Alive: " + std::to_string(activeBirdCount) + "/" + std::to_string(population->speciatingConfig.population) + "\n";
	txt += "Hit [K] to skip generation";
	mfont.Draw(txt.c_str(), 10.0f, 10.0f, 20.0f, Colors::White);

	return InputSystem::Get()->IsKeyPressed(KeyCode::ESCAPE);
}

bool GameState::RunXOR(float deltaTime)
{
	auto XORTest = [](ML::NEAT::NeuralNet& n, bool log) -> size_t
	{
		size_t fitness = 0;

		std::string message = "     > begin xor test\n        ( ";

		auto output = n.Evaluate({ 0.0, 0.0 });
		message += std::to_string(output[0]) + " ";
		fitness += (size_t)std::min(1.0 / ((0.0 - output[0]) * (0.0f - output[0])), 50.0);

		output = n.Evaluate({ 0.0, 1.0 });
		message += std::to_string(output[0]) + " ";
		fitness += (size_t)std::min(1.0 / ((1.0 - output[0]) * (1.0 - output[0])), 50.0);

		output = n.Evaluate({ 1.0, 0.0 });
		message += std::to_string(output[0]) + " ";
		fitness += (size_t)std::min(1.0 / ((1.0 - output[0]) * (1.0 - output[0])), 50.0);

		output = n.Evaluate({ 1.0, 1.0 });
		message += std::to_string(output[0]) + " ";
		fitness += (size_t)std::min(1.0 / ((0.0 - output[0]) * (0.0 - output[0])), 50.0);

		if (log)
		{
			message += ") fitness = " + std::to_string(fitness);
			LOG("%s", message.c_str());
		}

		return fitness;
	};

	ML::NEAT::Population p(2, 1);
	ML::NEAT::NeuralNet bestGuy;

	ML::NEAT::MutationConfig& mutationConfig = p.mutationConfig;
	mutationConfig.connection_mutate_chance = 0.65 * 0.5;
	mutationConfig.perturb_chance = 0.9;
	mutationConfig.crossover_chance = 0.75 * 0.5;
	mutationConfig.link_mutation_chance = 0.85 * 0.5;
	mutationConfig.node_mutation_chance = 0.5 * 0.5;
	mutationConfig.bias_mutation_chance = 0.2 * 0.5;
	mutationConfig.step_size = 0.1 * 0.5;
	mutationConfig.disable_mutation_chance = 0.2;
	mutationConfig.enable_mutation_chance = 0.2 * 0.5;

	size_t max_fitness = 0;
	while (max_fitness < 200)
	{
		size_t current_fitness = 0;
		size_t min_fitness = 100000;
		for (auto& s : p.species)
		{
			for (auto& g : s.genomes)
			{
				ML::NEAT::NeuralNet n;
				n.Initialize(g, p.neuralNetConfig);
				current_fitness = XORTest(n, false);
				if (current_fitness < min_fitness)
					min_fitness = current_fitness;
				if (current_fitness > max_fitness)
				{
					max_fitness = current_fitness;
					bestGuy = n;
				}
				g.fitness = current_fitness;
			}
		}

		LOG("Generation %zd successfuly tested. Species: %zd, Global min fitness: %zd, Global max fitness: %zd", p.Generation(), p.species.size(), min_fitness, max_fitness);
		p.NewGeneration();
	}

	XORTest(bestGuy, true);
	return true;
}




