#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/Math/Matrix4.h"
#include "../TEngine/Core/Math/Matrix4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(Matrix4Tests)
	{
	public:
		TEST_METHOD(AdditionOk)
		{
			Matrix4 m1 = Matrix4(1.f);
			Matrix4 m2 = Matrix4(2.f);

			Matrix4 m3 = m1 + m2;

			for (float32 f : m3.flat)
				Assert::AreEqual(f, 3.f);
		}

		TEST_METHOD(SubtractionOk)
		{
			Matrix4 m1 = Matrix4(1.f);
			Matrix4 m2 = Matrix4(2.f);

			Matrix4 m3 = m2 - m1;

			for (float32 f : m3.flat)
				Assert::AreEqual(f, 1.f);
		}

		TEST_METHOD(MultiplicationOk)
		{
			Matrix4 m1 = Matrix4(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2);
			Matrix4 m2 = Matrix4(3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3);

			Matrix4 m3 = m1 * m2;

			for (size i = 0; i < 4; i++)
			{
				for (size j = 0; j < 4; j++)
				{
					if (i == j)
						Assert::AreEqual(m3.m[i][j], 6.f);
					else
						Assert::AreEqual(m3.m[i][j], 0.f);
				}
			}
		}

		TEST_METHOD(EqAdditionOk)
		{
			Matrix4 m1 = Matrix4(1.f);
			Matrix4 m2 = Matrix4(2.f);

			m1 += m2;

			for (float32 f : m1.flat)
				Assert::AreEqual(f, 3.f);
		}

		TEST_METHOD(EqSubtractionOk)
		{
			Matrix4 m1 = Matrix4(1.f);
			Matrix4 m2 = Matrix4(2.f);

			m1 -= m2;

			for (float32 f : m1.flat)
				Assert::AreEqual(f, -1.f);
		}

		TEST_METHOD(EqMultiplicationOk)
		{
			Matrix4 m1 = Matrix4(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2);
			Matrix4 m2 = Matrix4(3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3);

			m1 *= m2;

			for (size i = 0; i < 4; i++)
			{
				for (size j = 0; j < 4; j++)
				{
					if (i == j)
						Assert::AreEqual(m1.m[i][j], 6.f);
					else
						Assert::AreEqual(m1.m[i][j], 0.f);
				}
			}
		}
	};
}
