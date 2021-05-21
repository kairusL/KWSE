#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace KWSE;
using namespace KWSE::Graphics;

namespace
{
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();


		// Functions to add 3D lines
		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
		void AddAABB(const Math::AABB& aabb, const Color& color);
		void AddSphere(const Math::Sphere& sphere, const Color& color, uint32_t slices, uint32_t rings);
		void AddTransform(const Math::Matrix4& transform);
		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color);

		// Functions to add screen lines
		void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color);
		void AddScreenRect(const Math::Rect& rect, const Color& color);
		void AddScreenCircle(const Math::Circle& circle, const Color& color);
		void AddScreenArc(const Math::Vector2& center, float radius, float fromAngle, float toAngle, const Color& color);
		void AddScreenDiamond(const Math::Vector2& center, float size, const Color& color);

		//void AddCone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color, bool fill);


		void Render(const Camera& camera);

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		// Unique ownership
		std::unique_ptr<VertexPC[]> mVertices2D;
		std::unique_ptr<VertexPC[]> mVertices3D;
		std::unique_ptr<VertexPC[]> mFillVertices;
		uint32_t mVertices2DCount = 0;
		uint32_t mVertex3DCount = 0;
		uint32_t mMaxVertexCount = 0;
		uint32_t mFillVertexCount = 0;

	};

	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		mVertexShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx", VertexPC::Format);
		mPixelShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx");
		mConstantBuffer.Initialize(sizeof(Math::Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount, true);

		mVertices2D = std::make_unique<VertexPC[]>(maxVertexCount);
		mVertices3D = std::make_unique<VertexPC[]>(maxVertexCount);
		mFillVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mVertices2DCount = 0;
		mVertex3DCount = 0;
		mMaxVertexCount = maxVertexCount;
	}
	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}

	void SimpleDrawImpl::AddScreenCircle(const Math::Circle & circle, const Color& color)
	{
		if (mVertices2DCount + 32 <= mMaxVertexCount)
		{
			float x = circle.center.x;
			float y = circle.center.y;
			float r = circle.radius;

			// Add line
			const float kAngle = Math::Constants::Pi / 8.0f;
			for (uint32_t i = 0; i < 16; ++i)
			{
				const float alpha = i * kAngle;
				const float beta = alpha + kAngle;
				const float x0 = x + (r * sin(alpha));
				const float y0 = y + (r * cos(alpha));
				const float x1 = x + (r * sin(beta));
				const float y1 = y + (r * cos(beta));
				mVertices2D[mVertices2DCount++] = { Math::Vector3(x0, y0, 0.0f), color };
				mVertices2D[mVertices2DCount++] = { Math::Vector3(x1, y1, 0.0f), color };
			}
		}
	}

	void SimpleDrawImpl::AddScreenArc(const Math::Vector2& center, float radius, float fromAngle, float toAngle, const Color& color)
	{
		// Check if we have enough space
		if (mVertices2DCount + 32 <= mMaxVertexCount)
		{
			float x = center.x;
			float y = center.y;
			float r = radius;

			// Add line
			const float kAngle = (toAngle - fromAngle) / 16.0f;
			for (uint32_t i = 0; i < 16; ++i)
			{
				const float alpha = i * kAngle + fromAngle;
				const float beta = alpha + kAngle;
				const float x0 = x + (r * cos(alpha));
				const float y0 = y + (r * sin(alpha));
				const float x1 = x + (r * cos(beta));
				const float y1 = y + (r * sin(beta));
				mVertices2D[mVertices2DCount++] = { Math::Vector3(x0, y0, 0.0f), color };
				mVertices2D[mVertices2DCount++] = { Math::Vector3(x1, y1, 0.0f), color };
			}
		}
	}
	void SimpleDrawImpl::AddScreenDiamond(const Math::Vector2& center, float size, const Color& color)
	{
		// Check if we have enough space
		if (mVertices2DCount + 8 <= mMaxVertexCount)
		{
			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x, center.y - size, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x + size, center.y, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x + size, center.y, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x, center.y + size, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x, center.y + size, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x - size, center.y, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x - size, center.y, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(center.x, center.y - size, 0.0f), color };
		}
	}
	void SimpleDrawImpl::AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color)
	{
		if (mVertices2DCount + 2 <= mMaxVertexCount)
		{
			mVertices2D[mVertices2DCount++] = VertexPC{ Math::Vector3(v0.x,v0.y,0.f),color };
			mVertices2D[mVertices2DCount++] = VertexPC{ Math::Vector3(v1.x,v1.y,0.f),color };
		}
	}
	void SimpleDrawImpl::AddScreenRect(const Math::Rect & rect, const Color & color)
	{
		if (mVertices2DCount + 8 <= mMaxVertexCount)
		{
			float l = rect.left;
			float t = rect.top;
			float r = rect.right;
			float b = rect.bottom;

			// Add lines
			mVertices2D[mVertices2DCount++] = { Math::Vector3(l, t, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(r, t, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(r, t, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(r, b, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(r, b, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(l, b, 0.0f), color };

			mVertices2D[mVertices2DCount++] = { Math::Vector3(l, b, 0.0f), color };
			mVertices2D[mVertices2DCount++] = { Math::Vector3(l, t, 0.0f), color };
		}

	}
	void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
	{
		if (mVertex3DCount + 2 <= mMaxVertexCount)
		{
			mVertices3D[mVertex3DCount++] = VertexPC{ v0,color };
			mVertices3D[mVertex3DCount++] = VertexPC{ v1,color };
		}
	}

	void SimpleDrawImpl::AddAABB(const Math::AABB & aabb, const Color & color)
	{
		// Check if we have enough space
		if (mVertex3DCount + 24 <= mMaxVertexCount)
		{
			float minX = aabb.center.x - aabb.extend.x;
			float minY = aabb.center.y - aabb.extend.y;
			float minZ = aabb.center.z - aabb.extend.z;
			float maxX = aabb.center.x + aabb.extend.x;
			float maxY = aabb.center.y + aabb.extend.y;
			float maxZ = aabb.center.z + aabb.extend.z;

			// Add lines
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, minZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, minZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, minZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, minY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, minY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, minZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, maxZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, maxZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, minZ), color };

			mVertices3D[mVertex3DCount++] = { Math::Vector3(maxX, maxY, minZ), color };
			mVertices3D[mVertex3DCount++] = { Math::Vector3(minX, maxY, minZ), color };
		}
		//const float minX = aabb.center.x - aabb.extend.x;
		//const float minY = aabb.center.y - aabb.extend.y;
		//const float minZ = aabb.center.z - aabb.extend.z;
		//const float maxX = aabb.center.x - aabb.extend.x;
		//const float maxY = aabb.center.y - aabb.extend.y;
		//const float maxZ = aabb.center.z - aabb.extend.z;

		//const Math::Vector3 NNN = { minX,minY,minZ };
		//const Math::Vector3 NNP = { minX,minY,maxZ };
		//const Math::Vector3 NPN = { minX,maxY,minZ };
		//const Math::Vector3 NPP = { minX,maxY,maxZ };
		//const Math::Vector3 PNN = { maxX,minY,minZ };
		//const Math::Vector3 PNP = { maxX,minY,maxZ };
		//const Math::Vector3 PPN = { maxX,maxY,minZ };
		//const Math::Vector3 PPP = { maxX,maxY,maxZ };


	}

	void SimpleDrawImpl::AddSphere(const Math::Sphere & sphere, const Color & color, uint32_t slices, uint32_t rings)
	{
	
		const float x = sphere.center.x;
		const float y = sphere.center.y;
		const float z = sphere.center.z;
		const float radius = sphere.radius;

		const uint32_t kSlices = Math::Max(3u, slices);
		const uint32_t kRings = Math::Max(2u, rings);
		const uint32_t kLines = (4 * kSlices * kRings) - (2 * kSlices);

		// Check if we have enough space
		if (mVertex3DCount + kLines <= mMaxVertexCount)
		{
			// Add lines
			const float kTheta = Math::Constants::Pi / (float)kRings;
			const float kPhi = Math::Constants::TwoPi / (float)kSlices;
			for (uint32_t j = 0; j < kSlices; ++j)
			{
				for (uint32_t i = 0; i < kRings; ++i)
				{
					const float a = i * kTheta;
					const float b = a + kTheta;
					const float ay = radius * cos(a);
					const float by = radius * cos(b);

					const float theta = j * kPhi;
					const float phi = theta + kPhi;

					const float ar = sqrt(radius * radius - ay * ay);
					const float br = sqrt(radius * radius - by * by);

					const float x0 = x + (ar * sin(theta));
					const float y0 = y + (ay);
					const float z0 = z + (ar * cos(theta));

					const float x1 = x + (br * sin(theta));
					const float y1 = y + (by);
					const float z1 = z + (br * cos(theta));

					const float x2 = x + (br * sin(phi));
					const float y2 = y + (by);
					const float z2 = z + (br * cos(phi));

					mVertices3D[mVertex3DCount++] = { Math::Vector3(x0, y0, z0), color };
					mVertices3D[mVertex3DCount++] = { Math::Vector3(x1, y1, z1), color };

					if (i < kRings - 1)
					{
						mVertices3D[mVertex3DCount++] = { Math::Vector3(x1, y1, z1), color };
						mVertices3D[mVertex3DCount++] = { Math::Vector3(x2, y2, z2), color };
					}
				}
			}
		}

	}

	void SimpleDrawImpl::AddTransform(const Math::Matrix4 & transform)
	{
		auto r = Math::GetRight(transform);
		auto u = Math::GetUp(transform);
		auto l = Math::GetLook(transform);
		auto p = Math::GetTranslation(transform);
		AddLine(p, p + r, Colors::Red);
		AddLine(p, p + u, Colors::Green);
		AddLine(p, p + l, Colors::Blue);
	}
	void SimpleDrawImpl::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
	{
		if (mFillVertexCount + 3 <= mMaxVertexCount)
		{
			mFillVertices[mFillVertexCount++] = VertexPC{ v0,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v1,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v2,color };
		}
	}

	//void SimpleDrawImpl::AddCone(const Math::Vector3& base, const Math::Vector3& direction, float radius, const Color& color, bool fill)
	//{
	//	constexpr int sectors = 8;
	//	auto side = Math::Normalize(Math::Cross(base, direction)) * radius;
	//	auto angle = 0.0f;
	//	auto angleStep = Math::Constants::TwoPi / sectors;
	//
	//	if (fill)
	//	{
	//		for (int i = 0; i < sectors; ++i)
	//		{
	//			auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
	//			auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
	//			auto v0 = Math::TransformNormal(side, matRot0);
	//			auto v1 = Math::TransformNormal(side, matRot1);
	//			sInstance->AddFace(base + v0, base + v1, base + direction, color);
	//			sInstance->AddFace(base + v0, base, base + v1, color);
	//			angle += angleStep;
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < sectors; ++i)
	//		{
	//			auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
	//			auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
	//			auto v0 = Math::TransformNormal(side, matRot0);
	//			auto v1 = Math::TransformNormal(side, matRot1);
	//			sInstance->AddLine(base + v0, base + direction, color);
	//			sInstance->AddLine(base + v0, base + v1, color);
	//			angle += angleStep;
	//		}
	//	}
	//}

	void SimpleDrawImpl::Render(const Camera& camera)
	{
		// Pass data to mesh buffer and draw 

		auto matView = camera.GetViewMatrix();
		auto matProj = camera.GetProjectionMatrix();
		auto transform = Math::Transpose(matView * matProj);
		mConstantBuffer.Update(&transform);
		mConstantBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixelShader.Bind();

		mMeshBuffer.Update(mVertices3D.get(), mVertex3DCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFillVertices.get(), mFillVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		const uint32_t width = GraphicsSystem::Get()->GetBackBufferWidth();
		const uint32_t height = GraphicsSystem::Get()->GetBackBufferHeight();
		Math::Matrix4 screenToNDC = { 2.0f / width, 0.f        ,0.f, 0.f,
									  0.f         , -2.f / height,0.f,0.f,
									  0.f         , 0.f        ,1.f,0.f,
									 -1.f         , 1.f        ,0.f,1.f, };
		mConstantBuffer.Update(&Math::Transpose(screenToNDC));
		mConstantBuffer.BindVS(0);
		mMeshBuffer.Update(mVertices2D.get(), mVertices2DCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mVertices2DCount = 0;
		mVertex3DCount = 0;
		mFillVertexCount = 0;
	}


	std::unique_ptr<SimpleDrawImpl> sInstance;
}

void KWSE::Graphics::SimpleDraw::AddLine(const Math::Vector3 & v0, const Math::Vector3 & v1, const Color & color)
{
	sInstance->AddLine(v0, v1, color);
}
void SimpleDraw::AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Color& color)
{
	AddLine(Math::Vector3(x0, y0, z0), Math::Vector3(x1, y1, z1), color);
}

void KWSE::Graphics::SimpleDraw::AddAABB(const Math::Vector3 & center, const Math::Vector3 & extend, const Color & color, bool fill)
{
	const float minX = center.x - extend.x;
	const float minY = center.y - extend.y;
	const float minZ = center.z - extend.z;
	const float maxX = center.x + extend.x;
	const float maxY = center.y + extend.y;
	const float maxZ = center.z + extend.z;

	const Math::Vector3 NNN = { minX,minY,minZ };
	const Math::Vector3 NNP = { minX,minY,maxZ };
	const Math::Vector3 NPN = { minX,maxY,minZ };
	const Math::Vector3 NPP = { minX,maxY,maxZ };
	const Math::Vector3 PNN = { maxX,minY,minZ };
	const Math::Vector3 PNP = { maxX,minY,maxZ };
	const Math::Vector3 PPN = { maxX,maxY,minZ };
	const Math::Vector3 PPP = { maxX,maxY,maxZ };

	if (fill)
	{
		// Front
		sInstance->AddFace(NNN, NPN, PPN, color);
		sInstance->AddFace(NNN, PPN, PNN, color);

		// Right
		sInstance->AddFace(PNN, PPN, PPP, color);
		sInstance->AddFace(PNN, PPP, PNP, color);

		// Back
		sInstance->AddFace(PNP, PPP, NPP, color);
		sInstance->AddFace(PNP, NPP, NNP, color);

		// Left
		sInstance->AddFace(NNP, NPP, NPN, color);
		sInstance->AddFace(NNP, NPN, NNN, color);

		// Top
		sInstance->AddFace(NPN, NPP, PPP, color);
		sInstance->AddFace(NPN, PPP, PPN, color);

		// Bottom
		sInstance->AddFace(NNP, NNN, PNN, color);
		sInstance->AddFace(NNP, PNN, PNP, color);
	}
	else
	{
		sInstance->AddLine(NNN, NNP, color);
		sInstance->AddLine(NNP, PNP, color);
		sInstance->AddLine(PNP, PNN, color);
		sInstance->AddLine(PNN, NNN, color);

		sInstance->AddLine(NNN, NPN, color);
		sInstance->AddLine(NNP, NPP, color);
		sInstance->AddLine(PNP, PPP, color);
		sInstance->AddLine(PNN, PPN, color);

		sInstance->AddLine(NPN, NPP, color);
		sInstance->AddLine(NPP, PPP, color);
		sInstance->AddLine(PPP, PPN, color);
		sInstance->AddLine(PPN, NPN, color);
	}


	//sInstance->AddLine({ minX, minY, minZ }, { minX, minY, maxZ }, color);
	//sInstance->AddLine({ minX, minY, maxZ }, { maxX, minY, maxZ }, color);
	//sInstance->AddLine({ maxX, minY, maxZ }, { maxX, minY, minZ }, color);
	//sInstance->AddLine({ maxX, minY, minZ }, { minX, minY, minZ }, color);
	//
	//
	//
	//sInstance->AddLine({ minX, minY, minZ }, { minX, maxY, minZ }, color);
	//sInstance->AddLine({ minX, minY, maxZ }, { minX, maxY, maxZ }, color);
	//sInstance->AddLine({ maxX, minY, maxZ }, { maxX, maxY, maxZ }, color);
	//sInstance->AddLine({ maxX, minY, minZ }, { maxX, maxY, minZ }, color);
	//
	//
	//
	//sInstance->AddLine({ minX, maxY, minZ }, { minX, maxY, maxZ }, color);
	//sInstance->AddLine({ minX, maxY, maxZ }, { maxX, maxY, maxZ }, color);
	//sInstance->AddLine({ maxX, maxY, maxZ }, { maxX, maxY, minZ }, color);
	//sInstance->AddLine({ maxX, maxY, minZ }, { minX, maxY, minZ }, color);
}
void KWSE::Graphics::SimpleDraw::AddCone(const Math::Vector3 & base, const Math::Vector3 & direction, float radius, const Color & color)
{
	int slices = 16;
	float thetaIncrement = Math::Constants::TwoPi / slices;
	std::vector<Math::Vector3> list;



	Math::Vector3 d = Math::Normalize(direction);
	float angle = acosf(Math::Dot(Math::Vector3::YAxis, d));
	Math::Vector3 rotationAxis = Math::Cross(Math::Vector3::YAxis, d);
	Math::Matrix4 rotationMatrix = Math::Matrix4::RotationAxis(rotationAxis, angle);



	for (float theta = 0; theta <= Math::Constants::TwoPi; theta += thetaIncrement)
	{
		Math::Vector3 vec3 = Math::TransformNormal(Math::Vector3{ radius * cosf(theta), 0.0f , radius * sinf(theta) }, rotationMatrix) + base;
		list.push_back(vec3);
	}
	float height = Math::Magnitude(direction);
	for (size_t i = 0; i < list.size() - 1; i++)
	{

		AddLine(list[i], list[i + 1], color);
		Math::Vector3 heightVec = Math::TransformNormal(Math::Vector3{ 0.0f , height , 0.0f }, rotationMatrix) + base;
		AddLine(list[i], heightVec, color);


	}

}
void KWSE::Graphics::SimpleDraw::AddBone(const Math::Matrix4 & transform)
{
	Math::Vector3 r = Math::GetRight(transform);
	Math::Vector3 u = Math::GetUp(transform);
	Math::Vector3 l = Math::GetLook(transform);
	Math::Vector3 p = Math::GetTranslation(transform);
	AddSphere(p, 0.025f, Colors::BlueViolet, 5, 6);
	AddLine(p, p + r*0.1f, Colors::Red);
	AddLine(p, p + u*0.1f, Colors::Green);
	AddLine(p, p + l*0.1f, Colors::Blue);
}
void KWSE::Graphics::SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void KWSE::Graphics::SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void KWSE::Graphics::SimpleDraw::AddScreenLine(const Math::Vector2 & v0, const Math::Vector2 & v1, const Color & color)
{
	sInstance->AddScreenLine(v0, v1, color);
}
void SimpleDraw::AddScreenLine(float x0, float y0, float x1, float y1, const Color& color)
{
	AddScreenLine(Math::Vector2(x0, y0), Math::Vector2(x1, y1), color);
}

void SimpleDraw::AddScreenRect(const Math::Rect& rect, const Color& color)
{
	sInstance->AddScreenRect(rect, color);
}

void SimpleDraw::AddScreenCircle(const Math::Circle& circle, const Color& color)
{
	sInstance->AddScreenCircle(circle, color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenCircle(const Math::Vector2& center, float r, const Color& color)
{
	AddScreenCircle(Math::Circle(center, r), color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenCircle(float x, float y, float r, const Color& color)
{
	AddScreenCircle(Math::Circle(x, y, r), color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenArc(const Math::Vector2& center, float r, float fromAngle, float toAngle, const Color& color)
{
	sInstance->AddScreenArc(center, r, fromAngle, toAngle, color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenDiamond(const Math::Vector2& center, float size, const Color& color)
{
	sInstance->AddScreenDiamond(center, size, color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenDiamond(float x, float y, float size, const Color& color)
{
	AddScreenDiamond(Math::Vector2(x, y), size, color);
}

void SimpleDraw::AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Color& color)
{
	AddScreenRect(Math::Rect(min.x, min.y, max.x, max.y), color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddScreenRect(float left, float top, float right, float bottom, const Color& color)
{
	AddScreenRect(Math::Rect(left, top, right, bottom), color);
}


void KWSE::Graphics::SimpleDraw::AddGroundPlane(float size, const Color & color)
{
	const float halfsize = size * 0.5f;
	for (float i = -halfsize; i <= halfsize; i += 1.0f)
	{
		AddLine({ i,0.0f,-halfsize }, { i,0.0f,halfsize }, color);
		AddLine({ -halfsize,0.0f,i }, { halfsize,0.0f,i }, color);
	}
}
void KWSE::Graphics::SimpleDraw::AddCylinder(const Math::Vector3 & base, const Math::Vector3 & direction, float radius, const Color & color)// base is the centre pos of bottom face 
{

	int slices = 16;
	int rings = 8;
	float increment = Math::Constants::TwoPi / static_cast<float>(slices);
	float ringRatio = 1.0f / rings;
	std::vector<Math::Vector3> list;



	Math::Vector3 d = Math::Normalize(direction);
	float angle = acosf(Math::Dot(d, Math::Vector3::YAxis));
	Math::Vector3 rotationAxis = Math::Cross(Math::Vector3::YAxis, d);
	Math::Matrix4 rotationMatrix = Math::Matrix4::RotationAxis(rotationAxis, angle);



	float height = Math::Magnitude(direction);
	for (int y = 0; y <= rings; y++)
	{
		for (float theta = 0; theta <= Math::Constants::TwoPi; theta += increment)
		{
			Math::Vector3 vec = Math::TransformNormal(
				Math::Vector3{ sinf(theta) * radius , height * y * ringRatio , cosf(theta) * radius }, rotationMatrix) + base;
			list.push_back(vec);
		}
	}
	int sectorCount = rings + 1;
	for (int y = 0; y <= rings; y++)
	{
		for (int x = 0; x < slices; x++)
		{



			AddLine(list[y * sectorCount + x], list[y * sectorCount + x + 1], color);
			if (y + 1 <= rings)
				AddLine(list[y * sectorCount + x], list[(y + 1) * sectorCount + x], color);
			if (y == 0 || y == rings)
			{
				Math::Vector3 centerVec =
					Math::TransformNormal(Math::Vector3{ 0.f, height * y * ringRatio , 0.0f }, rotationMatrix) + base;
				AddLine(list[y * sectorCount + x], centerVec, color);
			}
		}
	}
	//constexpr int sectors = 8;
	//auto side = Math::Normalize(Math::Cross(base, direction)) * radius;
	//auto angle = 0.0f;
	//auto angleStep = Math::Constants::TwoPi / sectors;
	//
	//
	//
	//for (int i = 0; i < sectors; ++i)
	//{
	//	auto matRot0 = Math::Matrix4::RotationAxis(direction, angle);
	//	auto matRot1 = Math::Matrix4::RotationAxis(direction, angle + angleStep);
	//	auto v0 = Math::TransformNormal(side, matRot0);
	//	auto v1 = Math::TransformNormal(side, matRot1);
	//	sInstance->AddLine(base + v0, base + direction + v0, color);
	//	sInstance->AddLine(base + v0, base + v1, color);
	//	sInstance->AddLine(base + direction + v0, base + direction + v1, color);
	//	angle += angleStep;
	//}
}

void KWSE::Graphics::SimpleDraw::AddSphere(const Math::Sphere& sphere, const Color& color, uint32_t slices, uint32_t rings)
{
	sInstance->AddSphere(sphere, color, slices, rings);
}


void SimpleDraw::AddSphere(const Math::Vector3& center, float radius, const Color& color, uint32_t slices, uint32_t rings)
{
	AddSphere(Math::Sphere(center, radius), color, slices, rings);
}

void SimpleDraw::AddSphere(float x, float y, float z, float radius, const Color& color, uint32_t slices, uint32_t rings)
{
	AddSphere(Math::Sphere(x, y, z, radius), color, slices, rings);
}


void KWSE::Graphics::SimpleDraw::AddTransform(const Math::Matrix4& transform)
{
	sInstance->AddTransform(transform);
}

void KWSE::Graphics::SimpleDraw::Render(const Camera & camera)
{
	sInstance->Render(camera);
}

void SimpleDraw::AddAABB(const Math::AABB& aabb, const Color& color)
{
	
	sInstance->AddAABB(aabb, color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddAABB(const Math::Vector3& min, const Math::Vector3& max, const Color& color)
{
	AddAABB(Math::AABB((min + max) * 0.5f, (max - min) * 0.5f), color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddAABB(const Math::Vector3& center, float radius, const Color& color)
{
	AddAABB(Math::AABB(center, Math::Vector3(radius, radius, radius)), color);
}

//----------------------------------------------------------------------------------------------------

void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
	AddAABB(Math::Vector3(minX, minY, minZ), Math::Vector3(maxX, maxY, maxZ), color);
}


