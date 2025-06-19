//
// Created by EgorRychkov on 16.06.2025.
//

#ifndef LOGISTICHELL_UNITRENDERQUAD_H
#define LOGISTICHELL_UNITRENDERQUAD_H

#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"

class UnitRenderQuad {
public:
    UnitRenderQuad(const std::string &texture_name, const sf::Vector2f &anchor_block, int render_priority,
                   const sf::Vector2f &position, const sf::Vector2f &size, float angle);

    void set_position(const sf::Vector2f &new_position);

    void set_rotation(float new_angle);

    std::string texture_name;
    std::vector<sf::Vector2f> vertices;
    int render_priority;
    sf::Vector2f anchor_block;
private:
    sf::Transform transform;
};


#endif //LOGISTICHELL_UNITRENDERQUAD_H
