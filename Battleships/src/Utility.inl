template <typename T>
std::string Utility::to_string(const T &value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}

template <typename T>
sf::Vector2i Utility::to_vector2i(sf::Vector2<T> vector)
{
	return sf::Vector2i(int(vector.x), int(vector.y));
}