// Copyright (c) 2016 Juan Delgado (JuDelCo)
// License: MIT License
// MIT License web page: https://opensource.org/licenses/MIT

#include "EntitasPP/SystemContainer.hpp"
#include "EntitasPP/Matcher.hpp"
#include "EntitasPP/Pool.hpp"
#include <iostream>

using namespace EntitasPP;

class DemoComponent : public IComponent {
	public:
		void Reset(const std::string& name1, const std::string& name2) {
			std::cout << "Created new entity: " << name1 << "," << name2 << std::endl;
		}
};

class DemoSystem : public IInitializeSystem, public IExecuteSystem, public ISetPoolSystem {
	public:
		void SetPool(Pool* pool) {
			mPool = pool;
		}
		void Initialize() {
			mPool->CreateEntity()->Add<DemoComponent>("foo", "bar");
			std::cout << "DemoSystem initialized" << std::endl;
		}
		void Execute() {
			/*
			pool管理着group，group管理着entity
			*/
			mPool->CreateEntity()->Add<DemoComponent>("foo", "bar");

			/*
			每一个matcher都会有一个自己的hash值,
			在构造matcher的时候，会传入componentidlist, 然后在matcher的构造函数中, 会计算hash值.
			然后GetGroup根据这个matcher的hash值，直接去group中的map去find就可以了
			*/
			auto entitiesCount = mPool->GetGroup(Matcher_AllOf(DemoComponent))->Count();
			std::cout << "There are " << entitiesCount << " entities with the component 'DemoComponent'" << std::endl;

			std::cout << "DemoSystem executed" << std::endl;
		}

	private:
		Pool* mPool;
};

int main(const int argc, const char* argv[]) {
	auto systems = std::make_shared<SystemContainer>();
	auto pool = std::make_shared<Pool>();

	systems->Add(pool->CreateSystem<DemoSystem>());
	systems->Initialize();

	for(unsigned int i = 0; i < 2; ++i) {
		systems->Execute();
	}

	return 0;
}
