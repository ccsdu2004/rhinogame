//from:https://github.com/ccsdu2004/objectfactory
#ifndef RHINO_OBJECT_FACTORY_H
#define RHINO_OBJECT_FACTORY_H
#include <map>
#include <memory>
#include <functional>
#include "rhino.h"

template<class Product,class ID>
class RHINO_EXPORT ObjectFactory
{
public:
	static Product* create(const ID& id)
	{
		auto itr = creator->find(id);
		if (itr != creator->end())
		{
			return itr->second();
		}
		return nullptr;
	}

	static std::map<ID,std::function<Product*()>>* creator;

	static void initialize()
	{
		if (!creator)
			creator = new std::map<ID,std::function<Product*()>>();
	}

	static void shutdown()
	{
		if (creator)
			delete creator;
		creator = nullptr;
	}

	template<class Target>
	static Product* createObject()
	{
		return new Target();
	};
};

template<class Product,class Target,class ID>
class ObjectRegister : public ObjectFactory<Product,ID>
{
public:
	ObjectRegister(const ID& id)
	{
		initialize();
		auto fn = &ObjectFactory::createObject<Target>;
		(*creator)[id] = fn;
	}
};

template<class Product,class ID>
std::map<ID,std::function<Product*()>>* ObjectFactory<Product,ID>::creator = nullptr;

#endif