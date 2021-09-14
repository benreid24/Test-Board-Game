#ifndef VALUE_HPP
#define VALUE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

using Value = std::vector<bool>;

void renderValue(sf::RenderTarget& target, const Value& value, const sf::Vector2f& pos);

#endif
