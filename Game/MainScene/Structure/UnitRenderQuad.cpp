//
// Created by EgorRychkov on 16.06.2025.
//

#include "UnitRenderQuad.h"

UnitRenderQuad::UnitRenderQuad(const std::string &texture_name, const sf::Vector2f &anchor_block, int render_priority,
                               const sf::Vector2f &position, const sf::Vector2f &size, float angle) {
    this->texture_name = texture_name;
    this->anchor_block = anchor_block;
    this->render_priority = render_priority;
    this->set_position(position);
    this->set_rotation(angle);
    this->vertices = {{0, 0}, {0, size.y}, {size.x, size.y}, {size.x, 0}};
}

void UnitRenderQuad::set_position(const sf::Vector2f &new_position) {
    this->transform.translate(new_position);
}

void UnitRenderQuad::set_rotation(float new_angle) {
    this->transform.rotate(new_angle);
}