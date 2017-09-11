// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: MIT License
// MIT License web page: https://opensource.org/licenses/MIT

#pragma once

#include "IComponent.hpp"
#include <vector>

namespace EntitasPP
{
typedef unsigned int ComponentId;
typedef std::vector<ComponentId> ComponentIdList;

struct ComponentTypeId
{
	public:
		template<typename T>
		static const ComponentId Get()
		{
			static_assert((std::is_base_of<IComponent, T>::value && ! std::is_same<IComponent, T>::value),
				"Class type must be derived from IComponent");
			// 这句代码决定过了, 同一个类型的Component必定只执行一次,即component跟 componentId是一一对应的
			// 对于一个entity, 有且仅有一个component
			// 从而可以用来，判定是否重复添加了该component
			static ComponentId id = mCounter++;
			return id;
		}

		static unsigned int Count()
		{
			return mCounter;
		}

	private:
		static unsigned int mCounter;
};
}
