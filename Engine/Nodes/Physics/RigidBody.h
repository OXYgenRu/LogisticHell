//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_RIGIDBODY_H
#define LOGISTICHELL_RIGIDBODY_H

#include <box2d/box2d.h>
#include "../Base/ContainerNode.h"
#include "World.h"

class RigidBody : public ContainerNode {
public:
    static std::shared_ptr<RigidBody>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<World> world, b2BodyDef &body_def,
           int render_priority = 0,
           int render_priority_layers = 10);

    explicit RigidBody(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void setup(std::shared_ptr<RigidBody> node, std::shared_ptr<World> world, b2BodyDef &body_def,
                      int render_priority_layers);

    sf::Vector2f sf_get_world_point(b2Vec2 local_point, EngineContext &ctx);

    b2Vec2 b2_get_local_point(sf::Vector2f &world_point, EngineContext &ctx);

    b2Vec2 b2_get_world_point(b2Vec2 local_point, EngineContext &ctx);

    b2BodyId body;
    float pixel_per_meter;
};


#endif //LOGISTICHELL_RIGIDBODY_H
