//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_RIGIDBODY_H
#define LOGISTICHELL_RIGIDBODY_H

#include <box2d/box2d.h>
#include "../Base/Node.h"
#include "World.h"
#include "RevoluteJoint.h"


class RigidBody : public Node {
public:
    static std::shared_ptr<RigidBody>
    create(const std::shared_ptr<World> &world, b2BodyDef &body_def,
           int render_priority = 0);

    explicit RigidBody(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    ~RigidBody();

    static void setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def);

    void destroy();

    void update(EngineContext &ctx);



    b2BodyId body_id;

    std::weak_ptr<World> world;
};


#endif //LOGISTICHELL_RIGIDBODY_H
