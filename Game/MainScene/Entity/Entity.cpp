//
// Created by EgorRychkov on 07.11.2025.
//

#include "Entity.h"
#include "../World/GameWorld.h"

std::shared_ptr<Entity>
Entity::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<GameWorld> &world,
               const unsigned int &entity_id, const sf::Vector2f &b2_position, const sf::Vector2f &b2_size,
               const float &density, const float &friction,
               const std::string &node_id,
               int render_priority) {
    auto node = std::make_shared<Entity>(parent, node_id, render_priority);
    Entity::setup(node, world, entity_id, b2_position, b2_size, density, friction);
    parent->add_node(node);
    return node;
}


void
Entity::setup(std::shared_ptr<Entity> &node, const std::shared_ptr<GameWorld> &world, const unsigned int &entity_id,
              const sf::Vector2f &b2_position, const sf::Vector2f &b2_size, const float &density,
              const float &friction) {
    node->world = world;
    node->entity_id = entity_id;

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = {b2_position.x, b2_position.y};

    node->rigid_body = RigidBody::create(world->get_world(), body_def, "EntityRigidBody");

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = density;
    shape_def.material.friction = friction;

    b2Polygon polygon;
    b2Vec2 vertices[4];
    vertices[0] = {float(b2_position.x) - b2_size.x / 2,
                   float(b2_position.y) + b2_size.y / 2};
    vertices[1] = {float(b2_position.x) - b2_size.x / 2,
                   float(b2_position.y) - b2_size.y / 2};
    vertices[2] = {float(b2_position.x) + b2_size.x / 2,
                   float(b2_position.y) - b2_size.y / 2};
    vertices[3] = {float(b2_position.x) + b2_size.x / 2,
                   float(b2_position.y) + b2_size.y / 2};
    b2Hull hull = b2ComputeHull(vertices, 4);
    polygon = b2MakePolygon(&hull, 0);


    CollisionPolygon::create(node->rigid_body, node->rigid_body,
                             shape_def,
                             polygon, "EntityCollisionPolygon");
}

void Entity::update(EngineContext &ctx) {
    this->set_position(this->rigid_body->get_position());
    this->set_rotation(this->rigid_body->get_rotation());
    this->set_origin(this->rigid_body->get_origin());
}


std::optional<sf::Vector2f> Entity::get_b2_position() const {
    return this->rigid_body->get_b2_position();
}

std::optional<float> Entity::get_b2_rotation() const {
    return this->rigid_body->get_b2_rotation();
}