#pragma once

namespace KWSE
{
	class AppState
	{
	public:
		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

	};

}