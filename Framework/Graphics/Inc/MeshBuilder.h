#pragma once


namespace KWSE::Graphics
{

	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(); // unit cube: -1 to 1
		static MeshPX CreateCubePX();
		static MeshPX CreateSkyboxPX();


		static MeshPX CreatePlanePX(uint32_t rows, uint32_t columns, float spacing); // facing positive Y
		static Mesh CreatePlane(uint32_t rows, uint32_t columns, float spacing); // facing positive Y

		static MeshPX CreateSpherePX( float radiu, int rings = 8, int slices = 16);
		static MeshPN CreateSpherePN( float radiu, int rings = 8, int slices = 16);
		static MeshPNX CreateSpherePNX( float radiu, int rings = 8, int slices = 16);
		static Mesh CreateSphere( float radiu, int rings = 8, int slices = 16);

		static MeshPX CreateCylinderPX(uint32_t height, uint32_t sector, float radius);
		static MeshPX CreateConePX(uint32_t rows, uint32_t columns, float spacing);// facing positive Y
	};
}