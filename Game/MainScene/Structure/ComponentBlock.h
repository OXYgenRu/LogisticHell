//
// Created by EgorRychkov on 17.06.2025.
//

#ifndef LOGISTICHELL_COMPONENTBLOCK_H
#define LOGISTICHELL_COMPONENTBLOCK_H

#include "iostream"
#include "memory"
#include "vector"
#include "UnitRenderQuad.h"
#include "../../../Engine/Nodes/UI/Collider.h"
#include "../../../Engine/Nodes/Physics/CollisionPolygon.h"

class Component;

class Unit;

class ComponentBlock : public Node {
public:
    static std::shared_ptr<ComponentBlock>
    create(const std::shared_ptr<Node> &parent, const sf::Vector2i &in_component_position,
           const std::shared_ptr<Component> &component, const unsigned int &block_id, const std::string &node_id,
           int render_priority = 0);

    explicit ComponentBlock(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<ComponentBlock> &node, const sf::Vector2i &in_component_position,
                      const std::shared_ptr<Component> &component, const unsigned int &block_id);


    ~ComponentBlock();

    void add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad);

    void delete_render_quads();

    std::vector<std::shared_ptr<UnitRenderQuad>> &get_render_quads();

    void set_unit(const std::shared_ptr<Unit> &new_unit);

    const sf::Vector2i &get_in_component_position();

    std::weak_ptr<Unit> get_weak_unit();

    std::weak_ptr<Component> get_weak_component();

    const unsigned int &get_block_id();

    std::shared_ptr<CollisionPolygon> collision_polygon;
    std::shared_ptr<UI::Collider> collider;
private:
    unsigned int block_id;
    sf::Vector2i in_component_position;
    std::weak_ptr<Unit> unit;
    std::vector<std::shared_ptr<UnitRenderQuad>> render_quads;
    std::weak_ptr<Component> component;
};


#endif //LOGISTICHELL_COMPONENTBLOCK_H
