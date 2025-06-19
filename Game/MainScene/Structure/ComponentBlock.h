//
// Created by EgorRychkov on 17.06.2025.
//

#ifndef LOGISTICHELL_COMPONENTBLOCK_H
#define LOGISTICHELL_COMPONENTBLOCK_H

#include "iostream"
#include "memory"
#include "vector"
#include "UnitRenderQuad.h"

class Unit;

class ComponentBlock {
public:
    ComponentBlock(const sf::Vector2i &in_component_position, const std::shared_ptr<Unit> &unit);

    void add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad);

    void delete_render_quads();

private:
    sf::Vector2i in_component_position;
    std::weak_ptr<Unit> unit;
    std::vector<std::shared_ptr<UnitRenderQuad>> render_quads;
};


#endif //LOGISTICHELL_COMPONENTBLOCK_H
