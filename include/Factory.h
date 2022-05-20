#pragma once

#include <map>
#include "GameObj.h"

using funcPtr = std::shared_ptr<GameObj>(*)(const ObjInfo&, const bool, b2World &);//zalman fix angle size objinfo

class ObjFactory
{  
public:

    ObjFactory();

	static std::shared_ptr<GameObj> create(const ObjInfo&, const bool , b2World &wold);

	static bool registerit(const Type_t& , const funcPtr);

private:
	static auto& getMap() 
    {
		static std::map<Type_t, funcPtr> map;
		return map;
	}
};

