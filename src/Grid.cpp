#include "Grid.hpp"

namespace
{
Value makeValue(std::uint8_t v) {
    Value r;
    r.reserve(6);
    for (int i = 0; i < 6; ++i) { r.push_back(((v >> i) & 1) == 1); }
    return r;
}
} // namespace

Grid::Grid() {
    std::vector<int> values;
    values.reserve(64);
    for (int i = 0; i < 64; ++i) { values.push_back(i); }

    // TODO - randomize order?

    grid.setSize(8, 8);
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) { grid(x, y) = makeValue(values[x * 8 + y]); }
    }
}

void Grid::render(sf::RenderTarget& target) {
    sf::RectangleShape rect({100, 100});
    sf::RectangleShape cover({10, 5});
    cover.setFillColor(sf::Color(207, 203, 151));

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            rect.setSize({100, 100});
            rect.setFillColor(sf::Color(255, 251, 189));
            rect.setPosition(100 * x, 100 * y);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            target.draw(rect);

            rect.setOutlineThickness(0);
            rect.setSize({40, 60});
            rect.setPosition(100 * x + 30, 100 * y + 15);
            rect.setFillColor(sf::Color(207, 203, 151));
            target.draw(rect);

            rect.setSize({30, 5});
            rect.setPosition(100 * x + 35, 100 * y + 20);
            rect.setFillColor(sf::Color::Black);

            for (bool v : grid(x, y).value) {
                cover.setPosition(rect.getPosition() + sf::Vector2f(10, 0));
                target.draw(rect);
                if (v) target.draw(cover);
                rect.setPosition(rect.getPosition() + sf::Vector2f(0, 10));
            }
        }
    }
}
