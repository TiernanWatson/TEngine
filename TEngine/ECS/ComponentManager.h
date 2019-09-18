#pragma once
#include <unordered_map>
#include "../Core/PortableTypes.h"

namespace TEngine
{
	template<class T>
	class ComponentManager
	{
	private:
		std::unordered_map<uint32, T> entityCompMap;

		ComponentManager();

	public:
		static ComponentManager<T>& Instance();


	};
}
