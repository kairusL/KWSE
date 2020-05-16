#pragma once

#include "Common.h"
#include "Colors.h"

namespace KWSE::Graphics
{
		struct VertexPC
	{
		constexpr VertexPC() = default;
		constexpr VertexPC(const Math::Vector3 position,
			const Color& color)noexcept
			: position(position),
			color(color)
			
		{}

		Math::Vector3 position;
		Color color;
	};

}