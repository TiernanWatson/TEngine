#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/PortableTypes.h"
#include "../TEngine/ECS/EntityManager.h"
#include "../TEngine/ECS/EntityManager.cpp"
#include "../TEngine/ECS/Components/Transform.h"
#include "../TEngine/ECS/Components/Transform.cpp"
#include "../TEngine/ECS/Components/MeshComponent.h"
#include "../TEngine/ECS/Components/MeshComponent.cpp"
#include "../TEngine/ECS/Metatype.h"
#include "../TEngine/ECS/Metatype.cpp"
#include "../TEngine/Core/Memory/Memory.h"
#include "../TEngine/Core/Memory/Memory.cpp"

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

		TEST_METHOD(ForEach)
		{
			EntityManager e;

			uint32 id = e.NewEntityWith<Transform>();
			uint32 id2 = e.NewEntityWith<Transform, MeshComponent>();

			e.ForEach<Transform>(
				[](Transform* t)
				{
					t->position = Vector3::one;
					t->rotation = Vector3::one;
					t->scale = Vector3::one;
				}
			);

			Transform t = e.GetComponent<Transform>(id);
			Transform t2 = e.GetComponent<Transform>(id2);

			Assert::AreEqual(1.f, t.position.x);
			Assert::AreEqual(1.f, t2.position.x);
		}
	};
}
