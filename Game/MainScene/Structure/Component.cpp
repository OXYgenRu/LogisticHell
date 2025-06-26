//
// Created by EgorRychkov on 11.06.2025.
//

#include "Component.h"
#include "Structure.h"
#include "../../../Engine/Application.h"

std::shared_ptr<Component>
Component::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Structure> &structure,
                  int render_priority) {
    std::shared_ptr<Component> node = std::make_shared<Component>(parent, render_priority);
    Component::setup(node, structure);
    parent->add_node(node);
    return node;
}

void Component::setup(std::shared_ptr<Component> &node, const std::shared_ptr<Structure> &structure) {
    node->structure = structure;
    node->grid_size = structure->blueprint->grid_size;
    node->collision_blocks.resize(node->grid_size.y,
                                  std::vector<std::shared_ptr<CollisionPolygon>>(node->grid_size.x));
    node->blocks.resize(node->grid_size.y,
                        std::vector<std::shared_ptr<ComponentBlock>>(node->grid_size.x));
}

void Component::update(EngineContext &ctx) {
    this->set_position(this->rigid_body->get_position());
    this->set_rotation(this->rigid_body->get_rotation());
    this->set_origin(this->rigid_body->get_origin());
}

void Component::create_block(const sf::Vector2i &position, BlueprintBlock &block, float block_side_size,
                             const std::shared_ptr<Component> &component) {
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
//    shape_def.material.friction = 0.3f;

    b2Polygon polygon;
    b2Vec2 vertices[4];
    vertices[0] = {float(position.x) * block_side_size - block_side_size / 2,
                   float(position.y) * block_side_size + block_side_size / 2};
    vertices[1] = {float(position.x) * block_side_size - block_side_size / 2,
                   float(position.y) * block_side_size - block_side_size / 2};
    vertices[2] = {float(position.x) * block_side_size + block_side_size / 2,
                   float(position.y) * block_side_size - block_side_size / 2};
    vertices[3] = {float(position.x) * block_side_size + block_side_size / 2,
                   float(position.y) * block_side_size + block_side_size / 2};
    b2Hull hull = b2ComputeHull(vertices, 4);
    polygon = b2MakePolygon(&hull, 0);

    this->collision_blocks[position.y][position.x] = CollisionPolygon::create(component, this->rigid_body,
                                                                              shape_def,
                                                                              polygon);
    this->blocks[position.y][position.x] = std::make_shared<ComponentBlock>(position, component);
}
