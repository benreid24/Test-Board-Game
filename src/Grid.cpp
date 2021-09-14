#include "Grid.hpp"

#include <BLIB/Media/Shapes.hpp>
#include <BLIB/Util/Random.hpp>

namespace
{
Value makeValue(std::uint8_t v) {
    Value r;
    r.reserve(6);
    for (int i = 0; i < 6; ++i) { r.push_back(((v >> i) & 1) == 1); }
    return r;
}

void shuffle(std::vector<int>& v) {
    for (unsigned int i = 0; i < 10000; ++i) {
        std::swap(v[bl::util::Random::get<unsigned int>(0, v.size())],
                  v[bl::util::Random::get<unsigned int>(0, v.size())]);
    }
}

} // namespace

Grid::Grid() {
    std::vector<int> values;
    values.reserve(64);
    for (int i = 0; i < 64; ++i) { values.push_back(i); }

    shuffle(values);

    grid.setSize(8, 8);
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) { grid(x, y) = makeValue(values[x * 8 + y]); }
    }
}

void Grid::render(sf::RenderTarget& target, const Value& filter) {
    sf::RectangleShape rect({100, 100});
    sf::RectangleShape cover({10, 5});
    cover.setFillColor(sf::Color(207, 203, 151));

    bl::shapes::GradientCircle circle(50.f);
    circle.setCenterColor(sf::Color(20, 230, 20, 170));
    circle.setOuterColor(sf::Color::Transparent);

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            rect.setSize({100, 100});
            rect.setFillColor(sf::Color(255, 251, 189));
            rect.setPosition(100 * x, 100 * y);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            target.draw(rect);

            renderValue(target,
                        grid(x, y).value,
                        {static_cast<float>(100 * x + 35), static_cast<float>(100 * y + 20)});

            if (grid(x, y).isValid(filter)) {
                circle.setPosition(x * 100 + 50, y * 100 + 45);
                target.draw(circle);
            }
        }
    }
}

void renderValue(sf::RenderTarget& target, const Value& value, const sf::Vector2f& pos) {
    sf::RectangleShape rect({40, 60});
    sf::RectangleShape cover({10, 5});

    rect.setPosition(pos);
    rect.setFillColor(sf::Color(207, 203, 151));
    target.draw(rect);

    rect.setSize({30, 5});
    rect.setPosition(pos.x + 5, pos.y + 3);
    rect.setFillColor(sf::Color::Black);
    cover.setFillColor(sf::Color(207, 203, 151));

    for (bool v : value) {
        cover.setPosition(rect.getPosition() + sf::Vector2f(10, 0));
        target.draw(rect);
        if (v) target.draw(cover);
        rect.setPosition(rect.getPosition() + sf::Vector2f(0, 10));
    }
}
