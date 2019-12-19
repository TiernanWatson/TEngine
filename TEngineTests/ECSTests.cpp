#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/PortableTypes.h"
#include "../TEngine/ECS/EntityManager.h"
#include "../TEngine/ECS/EntityManager.cpp"
#include "../TEngine/ECS/Components/Transform.h"
#include "../TEngine/ECS/Components/Transform.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(ECSTests)
	{
	public:
		TEST_METHOD(AddEntityOk)
		{
			EntityManager e;
			int id = e.NewEntity();

			Assert::AreEqual(id, 0);
		}
		
		TEST_METHOD(AddEntityWithOk)
		{
			EntityManager e;
			int id = e.NewEntityWith<Transform>();

			Assert::AreEqual(id, 0);
		}
	};
}
