#pragma once
#include<KWSE/Inc/KWSE.h>

// --Black-- //
class BlackState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Red-- //
class RedState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Orange-- //
class OrangeState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Yellow-- //
class YellowState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Green-- //
class GreenState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Cyan-- //
class CyanState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Blue-- //
class BlueState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

// --Purple-- //
class PurpleState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
};

