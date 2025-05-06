//
// Created by EgorRychkov on 28.04.2025.
//

#include "BaseBlock.h"
#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../Component/Component.h"

std::shared_ptr<BaseBlock> BaseBlock::create(std::shared_ptr<ContainerNode> parent,
                                             std::shared_ptr<RigidBody> rigid_body, b2Vec2 grid_position,
                                             float cell_size,
                                             int render_priority,
                                             int render_priority_layers) {
    auto node = std::make_shared<BaseBlock>(parent, render_priority);
    BaseBlock::setup(node, grid_position, rigid_body, render_priority_layers, cell_size);
    parent->add_node(node);
    return node;
}

void BaseBlock::setup(std::shared_ptr<BaseBlock> node, b2Vec2 grid_position, std::shared_ptr<RigidBody> rigid_body,
                      int render_priority_layers, float cell_size) {

    node->set_render_layers_count(render_priority_layers + 1);
    node->grid_position = grid_position;

    node->textured_quad = TexturedQuad::create(node);
//    node->textured_quad->texture.loadFromFile("blocks/TestConstructionBlock.png");
//
//    node->textured_quad->quad[0].texCoords = sf::Vector2f(0.f, 0.f);
//    node->textured_quad->quad[1].texCoords = sf::Vector2f(0.f, node->textured_quad->texture.getSize().y);
//    node->textured_quad->quad[2].texCoords = sf::Vector2f(node->textured_quad->texture.getSize().x,
//                                                          node->textured_quad->texture.getSize().y);
//    node->textured_quad->quad[3].texCoords = sf::Vector2f(node->textured_quad->texture.getSize().x, 0.f);

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 300.0f;
    shape_def.material.friction = 0.3f;

    b2Polygon polygon;
    node->vertices[0] = {grid_position.x * cell_size + -cell_size / 2, cell_size / 2 + grid_position.y * cell_size};
    node->vertices[1] = {grid_position.x * cell_size + -cell_size / 2, -cell_size / 2 + grid_position.y * cell_size};
    node->vertices[2] = {grid_position.x * cell_size + cell_size / 2, -cell_size / 2 + grid_position.y * cell_size};
    node->vertices[3] = {grid_position.x * cell_size + cell_size / 2, cell_size / 2 + grid_position.y * cell_size};
    b2Hull hull = b2ComputeHull(node->vertices, 4);
    polygon = b2MakePolygon(&hull, 0);
    node->collision_polygon = CollisionPolygon::create(node, rigid_body, shape_def, polygon);
}


void BaseBlock::update(EngineContext &ctx) {
    auto rigid_body = this->collision_polygon->rigid_body.lock();
    for (int i = 0; i < this->collision_polygon->polygon.count; i++) {
        this->textured_quad->quad[i].position = rigid_body->sf_get_world_point(this->vertices[i], ctx);
    }
}

