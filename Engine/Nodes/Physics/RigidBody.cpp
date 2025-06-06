//
// Created by EgorRychkov on 26.04.2025.
//

#include "RigidBody.h"
#include "../Base/Node.h"
#include "World.h"
#include "../../../Engine/Application.h"

std::shared_ptr<RigidBody>
RigidBody::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<World> &world, b2BodyDef &body_def,
                  int render_priority) {
    auto node = std::make_shared<RigidBody>(parent, render_priority);
    RigidBody::setup(node, world, body_def);
    parent->add_node(node);
    return node;
}

void RigidBody::setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def) {
    node->body = b2CreateBody(world->world_id, &body_def);
    node->pixel_per_meter = world->pixel_per_meter;
}

sf::Vector2f RigidBody::sf_get_world_point(b2Vec2 local_point, EngineContext &ctx) {
    b2Vec2 worldVertex = b2Body_GetWorldPoint(this->body, local_point);
    return {worldVertex.x * pixel_per_meter, -worldVertex.y * pixel_per_meter + ctx.app->window->getSize().y};
}

b2Vec2 RigidBody::b2_get_world_point(b2Vec2 local_point, EngineContext &ctx) {
    return b2Body_GetWorldPoint(this->body, local_point);
}

b2Vec2 RigidBody::b2_get_local_point(sf::Vector2f &world_point, EngineContext &ctx) {
    b2Vec2 world_vertex = b2Vec2(
            {world_point.x / pixel_per_meter,
             (ctx.app->window->getSize().y - world_point.y) / pixel_per_meter});

    return b2Body_GetLocalPoint(this->body, world_vertex);
}