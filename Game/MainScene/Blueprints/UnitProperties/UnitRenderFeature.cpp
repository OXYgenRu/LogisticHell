//
// Created by EgorRychkov on 11.06.2025.
//

#include "UnitRenderFeature.h"

UnitRenderFeature::UnitRenderFeature(const std::string &texture_name, const sf::Vector2i &anchor_block,
                                     int render_priority,
                                     const sf::Vector2f &position, const sf::Vector2f &size, float angle) {
    this->texture_name = texture_name;
    this->anchor_block = anchor_block;
    this->render_priority = render_priority;
    this->position = position;
    this->size = size;
    this->angle = angle;
}