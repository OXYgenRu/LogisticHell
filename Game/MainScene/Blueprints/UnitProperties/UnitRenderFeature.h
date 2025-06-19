//
// Created by EgorRychkov on 11.06.2025.
//

#ifndef LOGISTICHELL_UNITRENDERFEATURE_H
#define LOGISTICHELL_UNITRENDERFEATURE_H

#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"

class UnitRenderFeature {
public:
    UnitRenderFeature(const std::string &feature_name, const std::string &texture_name,
                      const sf::Vector2i &anchor_block, int render_priority,
                      const sf::Vector2f &position, const sf::Vector2f &size, float angle);


    std::string feature_name;
    std::string texture_name;
    sf::Vector2i anchor_block;
    int render_priority;
    sf::Vector2f position;
    sf::Vector2f size;
    float angle;
};


#endif //LOGISTICHELL_UNITRENDERFEATURE_H
