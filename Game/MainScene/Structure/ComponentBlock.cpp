//
// Created by EgorRychkov on 17.06.2025.
//

#include "ComponentBlock.h"

ComponentBlock::ComponentBlock(const sf::Vector2i &in_component_position, const std::shared_ptr<Unit> &unit) {
    this->in_component_position = in_component_position;
    this->unit = unit;
}

void ComponentBlock::add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad) {
    this->render_quads.push_back(new_quad);
}

void ComponentBlock::delete_render_quads() {
    this->render_quads.clear();
}