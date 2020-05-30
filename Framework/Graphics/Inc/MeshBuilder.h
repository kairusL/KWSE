#pragma once


namespace KWSE::Graphics
{

	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(); // unit cube: -1 to 1
		static MeshPX CreateCubePX();
	
		static MeshPX CreatePlanePX(uint32_t rows, uint32_t columns, float spacing); // facing positive Y

		//static MeshPX CreateCylinderPX(uint32_t rings, slices, float spacing);
	};
}