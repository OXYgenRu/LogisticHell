//
// Created by EgorRychkov on 26.04.2025.
//

#include "RigidBody.h"
#include "../Base/Node.h"
#include "World.h"
#include "../../../Engine/Application.h"
#include "cmath"

std::shared_ptr<RigidBody>
RigidBody::create(const std::shared_ptr<World> &world, b2BodyDef &body_def, const std::string &node_id,
                  int render_priority) {
    auto node = std::make_shared<RigidBody>(world, node_id, render_priority);
    RigidBody::setup(node, world, body_def);
    world->add_node(node);
    return node;
}

void
RigidBody::setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def) {
    node->body_id = b2CreateBody(world->world_id, &body_def);
    node->world = world;
    float pixel_per_meter = world->pixel_per_meter;

    b2Vec2 origin = b2Body_GetLocalCenterOfMass(node->body_id);
    sf::Vector2f origin_sf = {origin.x * pixel_per_meter, -origin.y * pixel_per_meter};
    b2Vec2 pos = b2Body_GetWorldCenterOfMass(node->body_id);

    b2Transform xf = b2Body_GetTransform(node->body_id);
    float angle = b2Rot_GetAngle(xf.q);
    sf::Vector2f sf_position = {pos.x * pixel_per_meter,
                                -pos.y * pixel_per_meter};
    node->set_origin(origin_sf);
    node->set_position(sf_position);
    node->set_rotation(-angle * 180.f / B2_PI);

    std::cout << "[PhysicalWrapper] " << "Body created\n";
}


RigidBody::~RigidBody() {
    this->destroy();
}

void RigidBody::destroy() {

    if (!b2Body_IsValid(this->body_id)) {
        return;
    }
    std::cout << "[PhysicalWrapper] " << "Body destroying\n";
    b2DestroyBody(this->body_id);
    std::cout << "[PhysicalWrapper] " << "Body destroyed\n";
}


void RigidBody::update(EngineContext &ctx) {
    if (b2Body_IsValid(this->body_id)) {
        float pixel_per_meter = world.lock()->pixel_per_meter;

        b2Vec2 origin = b2Body_GetLocalCenterOfMass(this->body_id);
        sf::Vector2f origin_sf = {origin.x * pixel_per_meter, -origin.y * pixel_per_meter};
        b2Vec2 pos = b2Body_GetWorldCenterOfMass(body_id);

        b2Transform xf = b2Body_GetTransform(this->body_id);
        float angle = b2Rot_GetAngle(xf.q);
        sf::Vector2f sf_position = {pos.x * pixel_per_meter,
                                    -pos.y * pixel_per_meter};
        this->set_origin(origin_sf);
        this->set_position(sf_position);
        this->set_rotation(-angle * 180.f / B2_PI);
    }
}

std::optional<sf::Vector2f> RigidBody::get_b2_position() const {
    if (!b2Body_IsValid(this->body_id)) {
        return std::nullopt;
    }
    b2Vec2 body_center_of_mass = b2Body_GetWorldCenterOfMass(this->body_id);
    return sf::Vector2f(body_center_of_mass.x, body_center_of_mass.y);
}

std::optional<float> RigidBody::get_b2_rotation() const {
    if (!b2Body_IsValid(this->body_id)) {
        return std::nullopt;
    }
    return b2Rot_GetAngle(b2Body_GetTransform(body_id).q);
}