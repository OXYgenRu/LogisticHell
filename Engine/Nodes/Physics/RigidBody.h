//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_RIGIDBODY_H
#define LOGISTICHELL_RIGIDBODY_H

#include <box2d/box2d.h>
#include <optional>
#include "../Base/Node.h"
#include "World.h"
#include "RevoluteJoint.h"

class RigidBody : public Node {
public:
    static std::shared_ptr<RigidBody>
    create(const std::shared_ptr<World> &world, b2BodyDef &body_def, const std::string &node_id,
           int render_priority = 0);

    explicit RigidBody(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}

    ~RigidBody();

    static void setup(const std::shared_ptr<RigidBody> &node, const std::shared_ptr<World> &world, b2BodyDef &body_def);

    void destroy();

    void update(EngineContext &ctx);

    std::optional<sf::Vector2f> get_b2_position() const;

    std::optional<float> get_b2_rotation() const;

    b2BodyId body_id;

    std::weak_ptr<World> world;
};


#endif //LOGISTICHELL_RIGIDBODY_H
