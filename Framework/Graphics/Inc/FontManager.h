#pragma once

#include "Font.h"
#include "Colors.h"

namespace
{
	struct TextCommand
	{
		TextCommand(std::wstring inStr, float inSize, float inX, float inY, KWSE::Graphics::Color inColor)
			: str(std::move(inStr))
			, size(inSize)
			, x(inX)
			, y(inY)
			, color(inColor)
		{}

		std::wstring str;
		float size, x, y;
		KWSE::Graphics::Color color;
	};
}

namespace KWSE::Graphics
{
	class Font;

	class FontManager
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static FontManager* Get();

	public:
		FontManager();
		~FontManager();

		void Initialize();
		void Terminate();

		FontManager(const FontManager&) = delete;
		FontManager& operator=(const FontManager&) = delete;

		void AddText(const char* str, float size, float x, float y, const Color& color);
		void Draw();

	private:
		std::vector<TextCommand> mTextCommands;
		KWSE::Graphics::Font mFont;
	};

} // namespace Graphics
