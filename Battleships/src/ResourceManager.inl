
template <typename Type, typename ID>
void ResourceManager<Type, ID>::load_resource(ID id, const std::string &filename)
{
	std::unique_ptr<Type> resource(new Type());
	if (resource->loadFromFile(filename) == false)
		exit(EXIT_FAILURE);

	insert_resource(id, std::move(resource));
}

template <typename Type, typename ID>
Type & ResourceManager<Type, ID>::get_resource(ID id)
{
	auto foundResource = mMap.find(id);
	assert(foundResource != mMap.end());

	return *foundResource->second;
}

template <typename Type, typename ID>
const Type & ResourceManager<Type, ID>::get_resource(ID id) const
{
	auto foundResource = mMap.find(id);
	assert(foundResource != mMap.end());

	return *foundResource->second;
}

template <typename Type, typename ID>
void ResourceManager<Type, ID>::insert_resource(ID id, std::unique_ptr<Type> resource)
{
	auto newResource = mMap.insert(std::make_pair(id, std::move(resource)));
	assert(newResource.second);
}
