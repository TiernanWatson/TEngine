#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/PortableTypes.h"
#include "../TEngine/ECS/EntityManager.h"
#include "../TEngine/ECS/EntityManager.cpp"
#include "../TEngine/ECS/Components/Transform.h"
#include "../TEngine/ECS/Components/Transform.cpp"
#include "../TEngine/ECS/Metatype.h"
#include "../TEngine/ECS/Metatype.cpp"

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

		TEST_METHOD(FindArchetype)
		{
			EntityManager e;
			
			Metatype t = Metatype::Create<Transform>();
			Archetype* a1 = e.AddArchetype(&t, 1);

			Archetype* a2 = e.FindArchetype(&t, 1);

			Assert::AreEqual(reinterpret_cast<uintptr>(a1), reinterpret_cast<uintptr>(a2));
		}
	};
}
