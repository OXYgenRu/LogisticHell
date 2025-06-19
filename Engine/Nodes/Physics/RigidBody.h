//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_RIGIDBODY_H
#define LOGISTICHELL_RIGIDBODY_H

#include <box2d/box2d.h>
#include "../Base/Node.h"
#include "World.h"
#include "RevoluteJoint.h"


struct JointIdHash {
    std::size_t operator()(const b2JointId &id) const noexcept {
        std::size_t h1 = std::hash<int32_t>{}(id.index1);
        std::size_t h2 = std::hash<uint16_t>{}(id.world0);
        std::size_t h3 = std::hash<uint16_t>{}(id.generation);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct JointIdEqual {
    bool operator()(const b2JointId &a, const b2JointId &b) const noexcept {
        return a.index1 == b.index1 &&
               a.world0 == b.world0 &&
               a.generation == b.generation;
    }
};

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

    b2BodyId body_id;

    std::weak_ptr<World> world;
};


#endif //LOGISTICHELL_RIGIDBODY_H
