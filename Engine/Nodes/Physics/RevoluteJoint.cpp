//
// Created by EgorRychkov on 17.06.2025.
//

#include "RevoluteJoint.h"
#include "World.h"
#include "RigidBody.h"

RevoluteJoint::RevoluteJoint(const std::shared_ptr<RigidBody> &body_a,
                             const std::shared_ptr<RigidBody> &body_b,
                             b2RevoluteJointDef &joint_def) {
    this->body_a = body_a;
    this->body_b = body_b;
    joint_def.bodyIdA = body_a->body_id;
    joint_def.bodyIdB = body_b->body_id;
    joint_def.collideConnected = true;
    this->joint_id = b2CreateRevoluteJoint(body_a->world.lock()->world_id, &joint_def);

}

RevoluteJoint::~RevoluteJoint() {
    std::cout << "asfd" << '\n';
    this->destroy();
}

void RevoluteJoint::destroy() {
    if (!b2Joint_IsValid(this->joint_id)) {
        return;
    }
    b2DestroyJoint(joint_id);
}

