#include "State.h"


namespace 
{ 
	float mTime=0.0f; 
}

using namespace KWSE::Graphics;


// --Black-- //
void BlackState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);
}

void BlackState::Update(float deltaTime)
{
	if (GetAsyncKeyState(VK_SPACE)&1)
	{
		if (mTime < KWSE::Core::TimeUtil::GetTime())
		{
			mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
			KWSE::MainApp().ChangeState("RedState");
		}
	}
}



// --Red-- //
void RedState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Red);

}

void RedState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("OrangeState");
	}
}


// --Orange-- //
void OrangeState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Orange);

}

void OrangeState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("YellowState");
	}
}


// --Yellow-- //
void YellowState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Yellow);

}

void YellowState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("GreenState");
	}
}

// --Green-- //
void GreenState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Green);

}

void GreenState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("CyanState");
	}
}


// --Cyan-- //
void CyanState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Cyan);

}

void CyanState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("BlueState");
	}
}



// --Blue-- //
void BlueState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Blue);

}

void BlueState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("PurpleState");
	}
}



// --Purple-- //
void PurpleState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Purple);

}

void PurpleState::Update(float deltaTime)
{
	if (mTime < KWSE::Core::TimeUtil::GetTime())
	{
		mTime = KWSE::Core::TimeUtil::GetTime() + 1.5f;
		KWSE::MainApp().ChangeState("BlackState");
	}
	
}

