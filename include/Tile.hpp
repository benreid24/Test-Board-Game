#ifndef TILE_HPP
#define TILE_HPP

#include "Value.hpp"

struct Tile {
    Tile() = default;

    Tile(const Value& value)
    : value(value) {}

    const Tile& operator=(const Value& v) {
        value = v;
        return *this;
    }

    bool isValid(const Value& filter) {
        for (unsigned int i = 0; i < filter.size(); ++i) {
            if (filter[i] != value[i]) return false;
        }
        return true;
    }

    Value value;
};

#endif
