#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KWSE::Math;

namespace MathTest
{
	TEST_CLASS(EngineMathTestTest)
	{
	public:

		TEST_METHOD(TestDot)
		{
			Vector3 v(1.0f,1.0f,1.0f);
			Vector3 u(1.0f,2.0f,3.0f);
			float dot = Dot(v, u);
			Assert::AreEqual(dot, 6.0f);
		}

		TEST_METHOD(TestMagnitudeSqr)
		{
			Vector3 v(1.0f, 2.0f, 3.0f);
			float magnitudeSqr = MagnitudeSqr(v);
			Assert::AreEqual(magnitudeSqr, 14.0f);
		}

		TEST_METHOD(TestMagnitude)
		{
			Vector3 v(1.0f, 2.0f, 3.0f);
			float magnitude = Magnitude(v);
			//// Tolerance of 0.000001f; 
			Assert::AreEqual(magnitude, 3.7416573f,0.000001f);
		}

		TEST_METHOD(TestDistanceSqr)
		{
			Vector3 v(2.0f, 2.0f, 2.0f);
			Vector3 u(1.0f, 0.0f, 1.0f);
			float distanceSqr = DistanceSqr(v, u);
			Assert::AreEqual(distanceSqr, 6.0f);
		}

		TEST_METHOD(TestDistance)
		{
			Vector3 v(7.0f, 4.0f, 3.0f);
			Vector3 u(17.0f, 6.0f, 2.0f);
			float distance = Distance(v, u);
			Assert::AreEqual(distance, 10.246951f,0.0000001f);
		}

		TEST_METHOD(TestNormalize)
		{
			Vector3 v(3.0f, 1.0f, 2.0f);
			Vector3 normalize = Normalize(v);
			Assert::AreEqual(normalize.x, 0.802f,0.001f);
			Assert::AreEqual(normalize.y, 0.267f,0.001f);
			Assert::AreEqual(normalize.z, 0.534f,0.001f);
		}

		TEST_METHOD(TestCross)
		{
			Vector3 u(5.0f, 3.0f, 2.0f);
			Vector3 v(8.0f, 10.0f, 20.0f);
			Vector3 cross = Cross(u, v);
			Assert::AreEqual(cross.x,40.0f );
			Assert::AreEqual(cross.y, -84.0f );
			Assert::AreEqual(cross.z, 26.0f);
		}
	};


}