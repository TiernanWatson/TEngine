#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/PortableTypes.h"
#include "../TEngine/ECS/EntityManager.h"
#include "../TEngine/ECS/EntityManager.cpp"
#include "../TEngine/ECS/Archetype.h"
#include "../TEngine/ECS/Archetype.cpp"
#include "../TEngine/ECS/Components/Transform.h"
#include "../TEngine/ECS/Components/MeshComponent.h"
#include "../TEngine/ECS/Components/PointLight.h"
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
		// AddEntity tests

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

		// Archetype tests

		TEST_METHOD(ArchetypeContains)
		{
			Metatype metas[] =
			{
				Metatype::Create<Transform>(),
				Metatype::Create<MeshComponent>()
			};

			Archetype* a = new Archetype(metas, 2);

			Assert::IsTrue(a->Contains(metas[0]));
			Assert::IsTrue(a->Contains(metas[1]));
			Assert::IsTrue(!a->Contains(Metatype::Create<ECSTests>()));
		}

		// ForEach Tests

		TEST_METHOD(ForEachNothing)
		{
			EntityManager e;

			bool used = false;
			e.ForEach<Transform>(
				[&used](Transform* t)
				{
					used = true;
				}
			);

			Assert::IsTrue(!used);
		}

		TEST_METHOD(ForEachOneComp)
		{
			EntityManager e;

			U32 id = e.NewEntityWith<Transform>();

			bool used = false;
			e.ForEach<Transform>(
				[&used](Transform* t)
				{
					used = true;
				}
			);

			Assert::IsTrue(used);
		}

		TEST_METHOD(ForEachMultiComp)
		{
			EntityManager e;

			U32 id = e.NewEntityWith<Transform, MeshComponent>();

			bool used = false;
			e.ForEach<Transform>(
				[&used](Transform* t)
				{
					used = true;
				}
			);

			Assert::IsTrue(used);
		}

		TEST_METHOD(ForEachMultiEntity)
		{
			EntityManager e;

			U32 id = e.NewEntityWith<Transform, MeshComponent>();
			U32 id2 = e.NewEntityWith<Transform, MeshComponent>();

			int useCount = 0;
			e.ForEach<Transform, MeshComponent>(
				[&useCount](Transform* t, MeshComponent* m)
				{
					useCount++;
				}
			);

			Assert::AreEqual(useCount, 2);
		}

		TEST_METHOD(ForEachNotSameArchetype)
		{
			EntityManager e;

			U32 id = e.NewEntityWith<Transform>();

			bool used = false;
			e.ForEach<Transform, MeshComponent>(
				[&used](Transform* t, MeshComponent* m)
				{
					used = true;
				}
			);

			Assert::IsTrue(!used);
		}

		TEST_METHOD(ForEachOnlyUseCorrectArch)
		{
			EntityManager e;

			U32 id = e.NewEntityWith<Transform, PointLight>();
			Transform& t1 = e.GetComponent<Transform>(id);
			t1.position = Vector3::kOne;

			U32 id2 = e.NewEntityWith<Transform, MeshComponent>();
			Transform& t2 = e.GetComponent<Transform>(id2);
			t2.position = Vector3::kZero;

			bool correct = true;
			e.ForEach<Transform, MeshComponent>(
				[&correct](Transform* t, MeshComponent* m)
				{
					if (t->position.x != 0)
						correct = false;
					if (t->position.y != 0)
						correct = false;
					if (t->position.z != 0)
						correct = false;
				}
			);

			bool correct2 = true;
			e.ForEach<Transform, PointLight>(
				[&correct2](Transform* t, PointLight* m)
				{
					if (t->position.x != 1)
						correct2 = false;
					if (t->position.y != 1)
						correct2 = false;
					if (t->position.z != 1)
						correct2 = false;
				}
			);

			Assert::IsTrue(correct && correct2);
		}

		// Data storage checks

		TEST_METHOD(DataCorrectOne)
		{
			EntityManager e;
			U32 id = e.NewEntityWith<Transform>();

			e.ForEach<Transform>(
				[](Transform* t)
				{
					t->position = Vector3::kOne;
					t->rotation = Vector3::kZero;
					t->scale = Vector3::kOne;
				}
			);

			bool correct = true;
			e.ForEach<Transform>(
				[&correct](Transform* t)
				{
					if (t->position.x != 1)
						correct = false;
					if (t->position.y != 1)
						correct = false;
					if (t->position.z != 1)
						correct = false;
					if (t->rotation.x != 0)
						correct = false;
					if (t->scale.z != 1)
						correct = false;
				}
			);

			Assert::IsTrue(correct);
		}

		TEST_METHOD(DataCorrectGetComp)
		{
			EntityManager e;
			U32 id = e.NewEntityWith<Transform>();

			Transform& t = e.GetComponent<Transform>(id);
			t.position = Vector3::kOne;

			bool correct = true;
			e.ForEach<Transform>(
				[&correct](Transform* t)
				{
					if (t->position.x != 1)
						correct = false;
					if (t->position.y != 1)
						correct = false;
					if (t->position.z != 1)
						correct = false;
				}
			);

			Assert::IsTrue(correct);
		}
	};
}
