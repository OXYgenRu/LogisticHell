//
// Created by EgorRychkov on 26.04.2025.
//

#include "RigidBody.h"
#include "../Base/Node.h"
#include "World.h"
#include "../../../Engine/Application.h"

std::shared_ptr<RigidBody>
RigidBody::create(const std::shared_ptr<World> &world, b2BodyDef &body_def,
                  int render_priority) {
    auto node = std::make_shared<RigidBody>(world, render_priority);
    RigidBody::setup(node, world, body_def);
    world->add_node(node);
    return node;
}

void
RigidBody::setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def) {
    node->body_id = b2CreateBody(world->world_id, &body_def);
}


RigidBody::~RigidBody() {
    this->destroy();
}

void RigidBody::destroy() {
    if (!b2Body_IsValid(this->body_id)) {
        return;
    }
    b2DestroyBody(this->body_id);
}
