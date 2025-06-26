//
// Created by EgorRychkov on 17.06.2025.
//

#ifndef LOGISTICHELL_COMPONENTBLOCK_H
#define LOGISTICHELL_COMPONENTBLOCK_H

#include "iostream"
#include "memory"
#include "vector"
#include "UnitRenderQuad.h"

class Component;

class Unit;

class ComponentBlock {
public:
    ComponentBlock(const sf::Vector2i &in_component_position, const std::shared_ptr<Component> &component);

    void add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad);

    void delete_render_quads();

    void set_unit(const std::shared_ptr<Unit> &new_unit);

    const sf::Vector2i &get_in_component_position();

    std::shared_ptr<Component> get_component();

private:
    sf::Vector2i in_component_position;
    std::weak_ptr<Unit> unit;
    std::vector<std::shared_ptr<UnitRenderQuad>> render_quads;
    std::weak_ptr<Component> component;
};


#endif //LOGISTICHELL_COMPONENTBLOCK_H
