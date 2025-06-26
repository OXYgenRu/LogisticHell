//
// Created by EgorRychkov on 17.06.2025.
//

#include "ComponentBlock.h"
#include "Component.h"

ComponentBlock::ComponentBlock(const sf::Vector2i &in_component_position, const std::shared_ptr<Component> &component) {
    this->in_component_position = in_component_position;
    this->component = component;
}

void ComponentBlock::add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad) {
    this->render_quads.push_back(new_quad);
}

void ComponentBlock::delete_render_quads() {
    this->render_quads.clear();
}

void ComponentBlock::set_unit(const std::shared_ptr<Unit> &new_unit) {
    this->unit = new_unit;
}

const sf::Vector2i &ComponentBlock::get_in_component_position() {
    return this->in_component_position;
}

std::shared_ptr<Component> ComponentBlock::get_component() {
    return component.lock();
}