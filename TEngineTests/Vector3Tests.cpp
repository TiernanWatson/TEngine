#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/Math/Vector3.h"
#include "../TEngine/Core/Math/Vector3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(Vector3Tests)
	{
	public:
		TEST_METHOD(TestVariablesOk)
		{
			Vector3 testV3 = Vector3(5.f, 2.f, 3.f);

			Assert::AreEqual(testV3.x, 5.f);
			Assert::AreEqual(testV3.y, 2.f);
			Assert::AreEqual(testV3.z, 3.f);
		}

		TEST_METHOD(NormalizesOk)
		{
			Vector3 testX = Vector3(10.f, 0.f, 0.f);
			testX.Normalize();
			Assert::AreEqual(testX.x, 1.f);
			Assert::AreEqual(testX.y, 0.f);
			Assert::AreEqual(testX.z, 0.f);

			Vector3 testY = Vector3(0.f, 10.f, 0.f);
			testY.Normalize();
			Assert::AreEqual(testY.x, 0.f);
			Assert::AreEqual(testY.y, 1.f);
			Assert::AreEqual(testY.z, 0.f);

			Vector3 testZ = Vector3(0.f, 0.f, 10.f);
			testZ.Normalize();
			Assert::AreEqual(testZ.x, 0.f);
			Assert::AreEqual(testZ.y, 0.f);
			Assert::AreEqual(testZ.z, 1.f);
		}

		TEST_METHOD(NormalizedOk)
		{
			Vector3 testX = Vector3(10.f, 0.f, 0.f);
			Vector3 returned = testX.Normalized();
			Assert::AreEqual(returned.x, 1.f);
			Assert::AreEqual(returned.y, 0.f);
			Assert::AreEqual(returned.z, 0.f);
		}

		TEST_METHOD(MagnitudeOk)
		{
			Vector3 test = Vector3(10.f, 0.f, 0.f);
			F32 result = test.Magnitude();
			Assert::AreEqual(result, 10.f);
		}

		TEST_METHOD(SqrMagnitudeOk)
		{
			Vector3 test = Vector3(10.f, 0.f, 0.f);
			F32 result = test.SqrMagnitude();
			Assert::AreEqual(result, 100.f);
		}
	};
}
