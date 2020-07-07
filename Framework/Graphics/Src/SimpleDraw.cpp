#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
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

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color);

		void Render(const Camera& camera);

	private: 
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		// Unique ownership
		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFillVertices;
		uint32_t mLineVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
		uint32_t mFillVertexCount = 0;
	
	};

	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		mVertexShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx", VertexPC::Format);
		mPixelShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx");
		mConstantBuffer.Initialize(sizeof(Math::Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount, true);

		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFillVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVertexCount = 0;
		mMaxVertexCount = maxVertexCount;
	}
	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}
	void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color)
	{
		if (mLineVertexCount +2 <=mMaxVertexCount)
		{
			mLineVertices[mLineVertexCount++] = VertexPC{ v0,color };
			mLineVertices[mLineVertexCount++] = VertexPC{ v1,color };
		}
	}
	void SimpleDrawImpl::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, const Color& color)
	{
		if (mFillVertexCount +3 <= mMaxVertexCount)
		{
			mFillVertices[mFillVertexCount++] = VertexPC{ v0,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v1,color };
			mFillVertices[mFillVertexCount++] = VertexPC{ v2,color };
		}

	}
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

		mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFillVertices.get(), mFillVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		mLineVertexCount = 0;
		mFillVertexCount = 0;
	}


	std::unique_ptr<SimpleDrawImpl> sInstance;
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

void KWSE::Graphics::SimpleDraw::AddLine(const Math::Vector3 & v0, const Math::Vector3 & v1, const Color & color)
{
	sInstance->AddLine(v0, v1, color);
}
void KWSE::Graphics::SimpleDraw::AddAABB(const Math::Vector3 & center, const Math::Vector3 & extend, const Color & color, bool fill)
{
	const float minX = center.x - extend.x;
	const float minY = center.y - extend.y;
	const float minZ = center.z - extend.z;
	const float maxX = center.x + extend.x;
	const float maxY = center.y + extend.y;
	const float maxZ = center.z + extend.z;

	const Math::Vector3 NNN = { minX, minY, minZ };
	const Math::Vector3 NNP = { minX, minY, maxZ };
	const Math::Vector3 NPN = { minX, maxY, minZ };
	const Math::Vector3 NPP = { minX, maxY, maxZ };
	const Math::Vector3 PNN = { maxX, minY, minZ };
	const Math::Vector3 PNP = { maxX, minY, maxZ };
	const Math::Vector3 PPN = { maxX, maxY, minZ };
	const Math::Vector3 PPP = { maxX, maxY, maxZ };

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
void KWSE::Graphics::SimpleDraw::AddGroundPlane(float size, const Color & color)
{
	const float halfsize = size*0.5f;
	for (float i = -halfsize; i <= halfsize; i+=1.0f)
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
void KWSE::Graphics::SimpleDraw::AddSphere(const Math::Vector3 & center, float radius, const Color & color, int rings, int slices)
{
	std::vector<Math::Vector3> vec3;
	//
	float phi = 0.0f;
	float theta = 0.0f;
	float thetaIncrement = Math::Constants::TwoPi / slices;
	float phiIncrement = Math::Constants::Pi / rings;

	for (uint32_t z = 0; z <= rings; ++z)
	{
		theta = 0.0f;
		for (uint32_t x = 0; x <= slices; ++x)
		{
			float newRadius = radius * sinf(phi);
			vec3.push_back(Math::Vector3{ newRadius*sinf(theta) , radius*cosf(phi), newRadius*-cosf(theta) }+center);
			theta += thetaIncrement;
		}
		phi += phiIncrement;
	}

	for (uint32_t y = 0; y < rings; ++y)
	{
		for (uint32_t x = 0; x < slices; ++x)
		{
			AddLine(vec3[y*slices + x], vec3[(y + 1)*slices + (x + 1)], color);
			AddLine(vec3[(y )*slices + (x+1)], vec3[y*slices + x], color);
			AddLine(vec3[(y+1)*slices + (x)], vec3[(y + 1)*slices + (x + 1)], color);
		}
	}

}
void KWSE::Graphics::SimpleDraw::AddCapsule(const Math::Vector3 & center, float height, float radius, const Color & color, int rings, int slices)
{
}
void KWSE::Graphics::SimpleDraw::AddTransform(const Math::Matrix4& transform)
{
	auto r = Math::GetRight(transform);
	auto u = Math::GetUp(transform);
	auto l = Math::GetLook(transform);
	auto p = Math::GetTranslation(transform);
	sInstance->AddLine(p, p + r, Colors::Red);
	sInstance->AddLine(p, p + u, Colors::Green);
	sInstance->AddLine(p, p + l, Colors::Blue);

}

void KWSE::Graphics::SimpleDraw::Render(const Camera & camera)
{
	sInstance->Render(camera);
}

