#ifndef TRAY_HPP
#define TRAY_HPP

#include "Value.hpp"
#include <SFML/Graphics.hpp>

class Tray {
public:
    Tray();

    void update();

    const Value& get() const;

    void render(sf::RenderTarget& target);

private:
    Value value;
    sf::Clock debounce;
};

#endif
