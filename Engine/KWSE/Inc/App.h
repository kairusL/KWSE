#pragma once


namespace KWSE
{

	class App
	{
	public:
		void Run();
		void Quit() { mRunning = false; }

	private:

		Core::Window mWindow;
		bool mRunning = false;
	};
}