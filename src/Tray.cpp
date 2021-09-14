#include "Tray.hpp"
#include <BLIB/Util/Random.hpp>

Tray::Tray() {
    // ?
}

const Value& Tray::get() const { return value; }

void Tray::update() {
    if (debounce.getElapsedTime().asSeconds() >= 0.7f) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && value.size() < 6) {
            debounce.restart();
            value.push_back(bl::util::Random::get<int>(0, 100) < 50);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            debounce.restart();
            value.clear();
        }
    }
}

void Tray::render(sf::RenderTarget& target) {
    sf::RectangleShape rect;
    rect.setSize({200, 800});
    rect.setFillColor(sf::Color(100, 100, 100));
    rect.setPosition(800, 0);
    target.draw(rect);

    renderValue(target, value, {880, 600});
}
