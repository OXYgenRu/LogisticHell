//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_RIGIDBODY_H
#define LOGISTICHELL_RIGIDBODY_H

#include <box2d/box2d.h>
#include "../Base/Node.h"
#include "World.h"

class RigidBody : public Node {
public:
    static std::shared_ptr<RigidBody>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<World> &world, b2BodyDef &body_def,
           int render_priority = 0);

    explicit RigidBody(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def);

    sf::Vector2f sf_get_world_point(b2Vec2 local_point, EngineContext &ctx);

    b2Vec2 b2_get_local_point(sf::Vector2f &world_point, EngineContext &ctx);

    b2Vec2 b2_get_world_point(b2Vec2 local_point, EngineContext &ctx);

    b2BodyId body;
    float pixel_per_meter;
};


#endif //LOGISTICHELL_RIGIDBODY_H
