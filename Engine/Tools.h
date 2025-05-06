//
// Created by EgorRychkov on 21.04.2025.
//

#ifndef LOGISTICHELL_TOOLS_H
#define LOGISTICHELL_TOOLS_H

#include "SFML/Graphics.hpp"

bool is_point_in_polygon(const sf::Vector2f &point, const std::vector<sf::Vector2f> &polygon) {
    int count = 0;
    int n = int(polygon.size());

    for (int i = 0; i < n; ++i) {
        const sf::Vector2f &a = polygon[i];
        const sf::Vector2f &b = polygon[(i + 1) % n];

        if ((a.y > point.y) != (b.y > point.y) and (b.y - a.y) != 0) {
            float t = (point.y - a.y) / (b.y - a.y);
            float xIntersection = a.x + t * (b.x - a.x);

            if (point.x < xIntersection)
                ++count;
        }
    }

    return (count % 2 == 1);
}

#endif //LOGISTICHELL_TOOLS_H
