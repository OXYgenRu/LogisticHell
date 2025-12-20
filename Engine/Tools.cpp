//
// Created by EgorRychkov on 09.11.2025.
//

#include "Tools.h"

bool Tools::is_point_in_polygon(const sf::Vector2f &point, const std::vector<sf::Vector2f> &polygon) {
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


std::vector<sf::Vector2f>
Tools::get_rectangle(const sf::Vector2f &center, const sf::Vector2f &size, const float &scale) {
    sf::Vector2f transformed_size = size * 0.5f * scale;
    return {{center.x - transformed_size.x, center.y - transformed_size.y},
            {center.x + transformed_size.y, center.y - transformed_size.y},
            {center.x + transformed_size.x, center.y + transformed_size.y},
            {center.x - transformed_size.x, center.y + transformed_size.y}};
}