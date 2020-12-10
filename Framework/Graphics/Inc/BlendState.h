#pragma once

namespace KWSE::Graphics
{
	class BlendState
	{
	public:
		static void ClearState();

	public:
		enum class Mode
		{
			Opaque,   //no mixing no blending or transparent
			AlphaBlend, //0.7 0.3 
			AlphaPremultiplied, // 0.4 0.6
			Additive // 0.5 1 ++until 1 (white)
		};

		BlendState() = default;
		~BlendState();

		BlendState(const BlendState&) = delete;
		BlendState& operator=(const BlendState&) = delete;

		void Initialize(Mode mode);
		void Terminate();

		void Set();

	private:
		ID3D11BlendState* mBlendState = nullptr;
	};
}
