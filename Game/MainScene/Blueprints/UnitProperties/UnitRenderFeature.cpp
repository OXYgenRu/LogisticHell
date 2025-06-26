//
// Created by EgorRychkov on 11.06.2025.
//

#include "UnitRenderFeature.h"

UnitRenderFeature::UnitRenderFeature(const std::string &feature_name, const std::string &texture_name,
                                     const sf::Vector2i &anchor_block,
                                     int render_priority,
                                     const sf::Vector2f &position, const sf::Vector2f &size, float angle) {
    this->texture_name = texture_name;
    this->anchor_block = anchor_block;
    this->render_priority = render_priority;
    this->position = position;
    this->vertices = {{0,      0},
                      {0,      size.y},
                      {size.x, size.y},
                      {size.x, 0}};
    this->angle = angle;
    this->feature_name = feature_name;
}

UnitRenderFeature::UnitRenderFeature(const std::string &feature_name, const std::string &texture_name,
                                     const sf::Vector2i &anchor_block, int render_priority,
                                     const sf::Vector2f &position, const std::vector<sf::Vector2f> &vertices,
                                     float angle) {
    this->texture_name = texture_name;
    this->anchor_block = anchor_block;
    this->render_priority = render_priority;
    this->position = position;
    this->vertices = vertices;
    this->angle = angle;
    this->feature_name = feature_name;
    if (this->vertices.size() != 4) {
        throw std::runtime_error("Unit render feature vertices count != 4");
    }
}