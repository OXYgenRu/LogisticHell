//
// Created by EgorRychkov on 21.04.2025.
//

#ifndef LOGISTICHELL_TOOLS_H
#define LOGISTICHELL_TOOLS_H

#include "SFML/Graphics.hpp"

namespace Tools {
    bool is_point_in_polygon(const sf::Vector2f &point, const std::vector<sf::Vector2f> &polygon);

    std::vector<sf::Vector2f> get_rectangle(const sf::Vector2f &center, const sf::Vector2f &size, const float &scale);
}

#endif //LOGISTICHELL_TOOLS_H


