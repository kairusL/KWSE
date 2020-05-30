#include "Precompiled.h"
#include "MeshTypes.h"
#include "MeshBuilder.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;



// position color
MeshPC KWSE::Graphics::MeshBuilder::CreateCubePC()
{
	MeshPC mesh;
	mesh.vertices.emplace_back(Vector3{ -0.5f, -0.5f, 0.0f }, Colors::AliceBlue);// bottom left  0
	mesh.vertices.emplace_back(Vector3{ -0.5f,  0.5f, 0.0f }, Colors::LightGoldenrodYellow);// top left     1
	mesh.vertices.emplace_back(Vector3{ 0.5f, 0.5f, 0.0f }, Colors::DarkBlue); // top right     2
	mesh.vertices.emplace_back(Vector3{ 0.5f, -0.5f, 0.0f }, Colors::Orange);     //bottom right   3

	mesh.vertices.emplace_back(Vector3{ -0.5f, -0.5f, 1.0f }, Colors::LightCyan);// bottom left  4
	mesh.vertices.emplace_back(Vector3{ -0.5f,  0.5f, 1.0f }, Colors::LightGray);// top left     5
	mesh.vertices.emplace_back(Vector3{ 0.5f, 0.5f,   1.0f }, Colors::DarkOrange); // top right   6
	mesh.vertices.emplace_back(Vector3{ 0.5f, -0.5f,  1.0f }, Colors::DarkGoldenrod);    //bottom right 7


	// Front
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);

	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(0);

	// Back
	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(5);
	mesh.indices.emplace_back(4);

	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(4);
	mesh.indices.emplace_back(7);

	// Right
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(3);

	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(7);
	mesh.indices.emplace_back(3);

	// Left
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(5);

	mesh.indices.emplace_back(5);
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(4);

	// Top
	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(1);

	mesh.indices.emplace_back(6);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(5);

	// Bottom
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(4);

	mesh.indices.emplace_back(4);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(7);

	return mesh;
}


//   0,0  +-----------------+1,0   //           5-----------------4
//	      |        ^        |	   //          /|                /|
//	      |        |        |	   //    1.0  0-----------------1 |
//	      | <------|------> |	   //	      | |      ^        | |
//	      |        |        | 	   //	      | |      +        | |
//	      |        v        |	   //	      | | <--- 0 +++>   | |
//	   0,1+-----------------+ 1,1  //	      | 7----- - -------| 6 1.0
								   //	      |/       v        |/
								   //	-1.0  2-----------------3 0.0
								   //      -1.0               1.0

MeshPX KWSE::Graphics::MeshBuilder::CreateCubePX()
{
	MeshPX mesh;
	// Front Face
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, -1.0f }, Vector2{0.0f,0.0f});		// top left     0
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, -1.0f }, Vector2{1.0f,0.0f});		// top right    1
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, -1.0f }, Vector2{0.0f,1.0f});		// bottom left  2
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, -1.0f }, Vector2{1.0f,1.0f});		//bottom right  3
	// Back Face
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, 1.0f }, Vector2{ 0.0f,0.0f });		// top left     4
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, 1.0f }, Vector2{ 1.0f,0.0f });		// top right    5
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, 1.0f }, Vector2{ 0.0f,1.0f });		// bottom left  6
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, 1.0f }, Vector2{ 1.0f,1.0f });		//bottom right  7
	// Right Face
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, -1.0f }, Vector2{ 0.0f,0.0f });		// top left     8
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, 1.0f }, Vector2{ 1.0f,0.0f });		// top right    9
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, -1.0f }, Vector2{ 0.0f,1.0f });		// bottom left  10
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, 1.0f }, Vector2{ 1.0f,1.0f });		//bottom right  11
	// Left Face
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, 1.0f }, Vector2{ 0.0f,0.0f });		// top left     12
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, -1.0f }, Vector2{ 1.0f,0.0f });		// top right    13
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, 1.0f }, Vector2{ 0.0f,1.0f });		// bottom left  14
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, -1.0f }, Vector2{ 1.0f,1.0f });		//bottom right  15
	// Top Face
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, 1.0f }, Vector2{ 0.0f,0.0f });		// top left     16
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, 1.0f }, Vector2{ 1.0f,0.0f });		// top right    17
	mesh.vertices.emplace_back(Vector3{ -1.0f,  1.0f, -1.0f }, Vector2{ 0.0f,1.0f });		// bottom left  18
	mesh.vertices.emplace_back(Vector3{  1.0f,  1.0f, -1.0f }, Vector2{ 1.0f,1.0f });		//bottom right  19
	// Bottom Face
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, 1.0f }, Vector2{ 0.0f,0.0f });		// top left     20
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, 1.0f }, Vector2{ 1.0f,0.0f });		// top right    21
	mesh.vertices.emplace_back(Vector3{  1.0f, -1.0f, -1.0f }, Vector2{ 0.0f,1.0f });		// bottom left  22
	mesh.vertices.emplace_back(Vector3{ -1.0f, -1.0f, -1.0f }, Vector2{ 1.0f,1.0f });		//bottom right  23


	// Front
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);

	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(2);

	// Back
	mesh.indices.emplace_back(4);
	mesh.indices.emplace_back(5);
	mesh.indices.emplace_back(6);

	mesh.indices.emplace_back(5);
	mesh.indices.emplace_back(7);
	mesh.indices.emplace_back(6);

	// Right
	mesh.indices.emplace_back(8 );
	mesh.indices.emplace_back(9 );
	mesh.indices.emplace_back(10);

	mesh.indices.emplace_back(9);
	mesh.indices.emplace_back(11);
	mesh.indices.emplace_back(10);

	// Left
	mesh.indices.emplace_back(12);
	mesh.indices.emplace_back(13);
	mesh.indices.emplace_back(14);

	mesh.indices.emplace_back(13);
	mesh.indices.emplace_back(15);
	mesh.indices.emplace_back(14);

	// Top
	mesh.indices.emplace_back(16);
	mesh.indices.emplace_back(17);
	mesh.indices.emplace_back(18);

	mesh.indices.emplace_back(17);
	mesh.indices.emplace_back(19);
	mesh.indices.emplace_back(18);

	// Bottom
	mesh.indices.emplace_back(20);
	mesh.indices.emplace_back(21);
	mesh.indices.emplace_back(22);

	mesh.indices.emplace_back(21);
	mesh.indices.emplace_back(23);
	mesh.indices.emplace_back(22);

	return mesh;
}


//            i*width+j   ______  i*width+j+1      
//                        |\    |              
//                        | \   |              
//                        |  \  |              
//                        |   \ |              
//                        |    \|              
//          (i+1)*width+j |-----|   (i+1)*width+j+1

MeshPX KWSE::Graphics::MeshBuilder::CreatePlanePX(uint32_t rows, uint32_t columns, float spacing)
{

	MeshPX mesh;
	//Ground plane y-axis stay 0 ,
	for (uint32_t z = 0; z <= rows; ++z)
	{
		for (uint32_t x	 = 0; x <= columns; ++x)
		{
			float xAxis = -0.5f* columns;
			float zAxis = 0.5f* rows;
			float xSpacing = x * spacing;
			float zSpacing = z * spacing;
			float u= static_cast<float>(x) / columns;
			float v= static_cast <float>(z) / rows;
			mesh.vertices.emplace_back(Vector3{ (xAxis* spacing + xSpacing) , (0.0f), (zAxis* spacing - zSpacing) }, Vector2{u,v});
			if (x!=columns)
			{

				// Draw 2 Triangles in one box;
				mesh.indices.emplace_back(z*rows+x);
				mesh.indices.emplace_back((z + 1)*rows + (x + 1));
				mesh.indices.emplace_back((z + 1)*rows + (x));

				mesh.indices.emplace_back(z*rows + x);
				mesh.indices.emplace_back((z)*rows + (x+1));
				mesh.indices.emplace_back((z+1)*rows + (x + 1));
			}
		}

	}

	return mesh;
}
