#pragma once

#include"Colors.h"
namespace KWSE::Graphics
{
	class Camera;
}

namespace KWSE::Graphics::SimpleDraw
{
	void StaticInitialize(uint32_t maxVertexCount = 10000);
	void StaticTerminate();


	void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);

	void AddAABB(const Math::Vector3& center, const Math::Vector3& extend, const Color& color, bool fill=false);

	

	void AddCone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color);

	void AddCylinder(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color);

	void AddSphere(const Math::Vector3& center, float radius, const Color& color, int rings = 8, int slices = 16);

	void AddCapsule(const Math::Vector3& center, float height, float radius, const Color& color, int rings = 8, int slices = 16);

	void AddTransform(const Math::Matrix4& transform);

	void AddGroundPlane(float size, const Color& color = Colors::DarkGray);


	void AddTransform(const Math::Matrix4& transform);
	void Render(const Camera& camera);

}