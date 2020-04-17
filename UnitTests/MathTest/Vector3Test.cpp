#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KWSE::Math;

namespace MathTest
{
	TEST_CLASS(Vector3Test)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			Vector3 v;
			Assert::AreEqual(v.x,0.0f);
			Assert::AreEqual(v.y,0.0f);
			Assert::AreEqual(v.z,0.0f);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Vector3 v(1.0f,1.0f,1.0f);
			Vector3 u = v;

			Assert::AreEqual(v.x, u.x);
			Assert::AreEqual(v.y, u.y);
			Assert::AreEqual(v.z, u.z);
		}

		TEST_METHOD(TestEqualOperator)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(1.0f, 1.0f, 1.0f);
			
			Assert::IsTrue(v == u);
		}

		TEST_METHOD(TestNegativeOperator)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(-1.0f, -1.0f, -1.0f);

			Assert::AreEqual(-v.x,u.x);
			Assert::AreEqual(-v.y,u.y);
			Assert::AreEqual(-v.z,u.z);
		}

		TEST_METHOD(TestPlus)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(2.0f, 2.0f, 2.0f);
			Vector3 oV = u + v;

			Assert::AreEqual(oV.x , 3.0f);
			Assert::AreEqual(oV.y , 3.0f);
			Assert::AreEqual(oV.z , 3.0f);
		}

		TEST_METHOD(TestMinus)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(2.0f, 2.0f, 2.0f);
			Vector3 oV = u - v;

			Assert::AreEqual(oV.x, 1.0f);
			Assert::AreEqual(oV.y, 1.0f);
			Assert::AreEqual(oV.z, 1.0f);
		}

		TEST_METHOD(TestTimes)
		{
			Vector3 v(2.0f, 2.0f, 2.0f);
			Vector3 oV = v*2.0f;

			Assert::AreEqual(oV.x, 4.0f);
			Assert::AreEqual(oV.y, 4.0f);
			Assert::AreEqual(oV.z, 4.0f);
		}

		TEST_METHOD(TestDivide)
		{
			Vector3 v(4.0f, 4.0f, 4.0f);
			Vector3 oV = v / 2.0f;

			Assert::AreEqual(oV.x, 2.0f);
			Assert::AreEqual(oV.y, 2.0f);
			Assert::AreEqual(oV.z, 2.0f);
		}

		TEST_METHOD(TestPlusEqual)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(2.0f, 2.0f, 2.0f);
			v += u;

			Assert::AreEqual(v.x, 3.0f);
			Assert::AreEqual(v.y, 3.0f);
			Assert::AreEqual(v.z, 3.0f);
		}

		TEST_METHOD(TestMinusEqual)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			Vector3 u(2.0f, 2.0f, 2.0f);
			v -= u;

			Assert::AreEqual(v.x, -1.0f);
			Assert::AreEqual(v.y, -1.0f);
			Assert::AreEqual(v.z, -1.0f);
		}

		TEST_METHOD(TestTimesEqual)
		{
			Vector3 v(1.0f, 1.0f, 1.0f);
			v *= 2.0f;

			Assert::AreEqual(v.x, 2.0f);
			Assert::AreEqual(v.y, 2.0f);
			Assert::AreEqual(v.z, 2.0f);
		}

		TEST_METHOD(TestDividedEqual)
		{
			Vector3 v(10.0f, 10.0f, 10.0f);
			v /= 2.0f;

			Assert::AreEqual(v.x, 5.0f);
			Assert::AreEqual(v.y, 5.0f);
			Assert::AreEqual(v.z, 5.0f);
		}

	};


}
