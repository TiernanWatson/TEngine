#pragma once
#include <unordered_map>
#include "../Core/PortableTypes.h"
#include "EntityManager.h"

namespace TEngine
{
	template<typename T>
	class ComponentManager
	{
	public:
		T GetByEntity(uint32 id) const;

		T AddToEntity(uint32 id);

		static ComponentManager<T>& Main();

	private:
		T componentArr[MAX_ENTITIES];

		size currentIndex = 0;

		std::unordered_map<uint32, size> entityIndexMap;
	};

	template<typename T>
	inline T ComponentManager<T>::GetByEntity(uint32 id) const
	{
		size index = entityIndexMap.at(id);
		return componentArr[index];
	}

	template<typename T>
	inline T ComponentManager<T>::AddToEntity(uint32 id)
	{
		componentArr[currentIndex] = T();
		entityIndexMap[id] = currentIndex;
		currentIndex++;

		return componentArr[currentIndex - 1];
	}

	template<typename T>
	ComponentManager<T>& ComponentManager<T>::Main()
	{
		static ComponentManager<T> instance;
		return instance;
	}
}
