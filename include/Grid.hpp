#ifndef GRID_HPP
#define GRID_HPP

#include "Tile.hpp"
#include <BLIB/Containers/Vector2d.hpp>
#include <SFML/Graphics.hpp>

class Grid {
public:
    Grid();

    void render(sf::RenderTarget& target, const Value& filter);

private:
    bl::container::Vector2D<Tile> grid;
};

#endif
