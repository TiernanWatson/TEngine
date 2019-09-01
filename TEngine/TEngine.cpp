// TEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Core/PortableTypes.h"
#include "Core/Memory/StackAllocator.h"
#include "Core/Math/Vector4.h"

int main()
{
    std::cout << "Hello World!\n";

	TEngine::size vsize = sizeof(TEngine::Vector4);

	TEngine::StackAllocator allocator(4 * vsize);

	TEngine::Vector4* myVector = reinterpret_cast<TEngine::Vector4*>(allocator.Alloc(vsize));

	*myVector = TEngine::Vector4();

	std::cout << "Stored " << myVector->ToString() << " at: " << myVector << " with size of: " << vsize << std::endl;
}

