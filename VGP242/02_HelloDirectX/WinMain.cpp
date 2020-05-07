#include <KWSE/Inc/KWSE.h>
#include "State.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{

	// States
	KWSE::MainApp().AddState<BlackState>("BlackState");
	KWSE::MainApp().AddState<RedState>("RedState");
	KWSE::MainApp().AddState<OrangeState>("OrangeState");
	KWSE::MainApp().AddState<YellowState>("YellowState");
	KWSE::MainApp().AddState<GreenState>("GreenState");
	KWSE::MainApp().AddState<CyanState>("CyanState");
	KWSE::MainApp().AddState<BlueState>("BlueState");
	KWSE::MainApp().AddState<PurpleState>("PurpleState");

	KWSE::MainApp().Run({ L"Hello DirectX", 1280, 720 });

	return 0;
}