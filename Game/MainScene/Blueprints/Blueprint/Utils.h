//
// Created by EgorRychkov on 31.05.2025.
//

#ifndef LOGISTICHELL_UTILS_H
#define LOGISTICHELL_UTILS_H

#include "functional"
#include "SFML/Graphics.hpp"

namespace std {
    template<>
    struct hash<sf::Vector2i> {
        std::size_t operator()(const sf::Vector2i &v) const noexcept {
            std::size_t h1 = std::hash<int>()(v.x);
            std::size_t h2 = std::hash<int>()(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}

#endif //LOGISTICHELL_UTILS_H
