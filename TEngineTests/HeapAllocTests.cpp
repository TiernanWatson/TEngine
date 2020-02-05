#include "pch.h"
#include "CppUnitTest.h"
#include "../TEngine/Core/Memory/HeapAllocator.h"
#include "../TEngine/Core/Memory/HeapAllocator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TEngine;

namespace TEngineTests
{
	TEST_CLASS(HeapAllocTests)
	{
	public:
		TEST_METHOD(AllocNormal)
		{
			HeapAllocator myHeap(100);
			void* ptr1 = myHeap.Alloc(1);
			Assert::IsNotNull(ptr1);
		}

		TEST_METHOD(AllocTooBig)
		{
			HeapAllocator myHeap(100);
			void* ptr = myHeap.Alloc(120);
			Assert::IsNull(ptr);
		}

		TEST_METHOD(AllocFullSize)
		{
			HeapAllocator myHeap(100);
			void* ptr = myHeap.Alloc(100);
			Assert::IsNull(ptr);
		}

		TEST_METHOD(OneObjAllocateSize)
		{
			HeapAllocator myHeap(100);
			void* ptr = myHeap.Alloc(10);
			Assert::AreEqual<size_t>(10, (size_t)myHeap.GetActiveSize());
		}

		TEST_METHOD(OneObjDeallocateSize)
		{
			HeapAllocator myHeap(100);
			void* ptr = myHeap.Alloc(10);
			myHeap.Free(ptr);
			Assert::AreEqual<size_t>(0, (size_t)myHeap.GetActiveSize());
		}
	};
}
