// TEngineBenchmarks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../TEngine/Core/Exception.h"
#include "../TEngine/Core/Exception.cpp"
#include "../TEngine/Core/Memory/Memory.h"
#include "../TEngine/Core/Memory/HeapAllocator.h"
#include "../TEngine/Core/Memory/HeapAllocator.cpp"
#include "../TEngine/Core/Memory/StackAllocator.h"
#include "../TEngine/Core/Memory/StackAllocator.cpp"
#include "../TEngine/Core/Memory/PoolAllocator.h"
#include "../TEngine/Core/Memory/PoolAllocator.cpp"
#include "../TEngine/Core/Memory/RBTree.h"
#include "../TEngine/Core/Memory/RBTree.cpp"
#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;

int main()
{
	/*TEngine::HeapAllocator allocat(1024 * 1024);
	for (int i = 0; i < 1000; i++)
	{
		void* ptr = allocat.Alloc(16);
	}*/
	std::chrono::high_resolution_clock clock;
	
	//TEngine::HeapAllocator allocat(1024 * 1024);
	//TEngine::StackAllocator allocat(1024 * 1024);
	TEngine::PoolAllocator allocat(8, 100000);
	TimePoint start = clock.now();
	for (int i = 0; i < 100000; i++)
	{
		void* ptr = allocat.Alloc();
	}
	TimePoint end = clock.now();

	TimePoint s2 = clock.now();
	for (int i = 0; i < 100000; i++)
	{
		void* ptr = malloc(8);
	}
	TimePoint e2 = clock.now();

	double t1 = (end-start).count() * 1e-6;
	double t2 = (e2 - s2).count() * 1e-6;

	printf("Heap took: %fms and malloc took %fms", t1, t2);
	return 0;
}

