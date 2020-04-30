#include "Precompiled.h"

#include "KWSE.h"

KWSE::App& KWSE::MainApp()
{
	static App sApp;

	return sApp;
}