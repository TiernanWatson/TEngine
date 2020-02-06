#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/Memory/PoolAllocator.h"
#include "../TEngine/Core/Memory/PoolAllocator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(PoolAllocTests)
	{
	public:
		TEST_METHOD(AllocNormal)
		{
			PoolAllocator pool(8, 10);
			void* ptr = pool.Alloc();
			Assert::IsNotNull(ptr);
		}

		TEST_METHOD(CorrectDistance)
		{
			PoolAllocator pool(8, 10);
			void* ptr1 = pool.Alloc();
			void* ptr2 = pool.Alloc();
			int diff = (uintptr)ptr2 - (uintptr)ptr1;
			Assert::AreEqual(diff, 8);
		}
	};
}
