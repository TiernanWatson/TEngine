#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/Memory/StackAllocator.h"
#include "../TEngine/Core/Memory/StackAllocator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(StackAllocTests)
	{
	public:
		TEST_METHOD(AllocNormal)
		{
			StackAllocator stack(100);
			void* ptr = stack.Alloc(8, 8);
			Assert::IsNotNull(ptr);
		}

		TEST_METHOD(AlignmentTest)
		{
			StackAllocator stack(100);
			void* ptr = stack.Alloc(16, 16);
			int misalign = (uintptr)ptr & 15;
			Assert::AreEqual(misalign, 0);
		}

		TEST_METHOD(CorrectDistance)
		{
			StackAllocator stack(100);
			void* ptr1 = stack.Alloc(8, 8);
			void* ptr2 = stack.Alloc(8, 8);
			int diff = (uintptr)ptr2 - (uintptr)ptr1;
			Assert::AreEqual(diff, 8);
		}
	};
}
