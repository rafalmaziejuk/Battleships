#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Type, typename ID>
class ResourceManager
{
private:
	std::map<ID, std::unique_ptr<Type>>	mMap;

private:
	void insert_resource(ID id, std::unique_ptr<Type> resource);

public:
	void load_resource(ID id, const std::string& filename);
	Type & get_resource(ID id);
	const Type & get_resource(ID id) const;
};

#include "ResourceManager.inl"