#ifndef GRID_HPP
#define GRID_HPP

#include "Tile.hpp"
#include <SFML/Graphics.hpp>
#include <BLIB/Containers/Vector2d.hpp>

class Grid {
public:
    Grid();

    void render(sf::RenderTarget& target);

private:
    bl::container::Vector2D<Tile> grid;
};

#endif
