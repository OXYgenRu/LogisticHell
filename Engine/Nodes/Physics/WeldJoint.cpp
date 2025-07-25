//
// Created by EgorRychkov on 03.07.2025.
//

#include "WeldJoint.h"


#include "World.h"
#include "RigidBody.h"

WeldJoint::WeldJoint(const std::shared_ptr<RigidBody> &body_a,
                             const std::shared_ptr<RigidBody> &body_b,
                             b2WeldJointDef &joint_def) {
    this->body_a = body_a;
    this->body_b = body_b;
    joint_def.bodyIdA = body_a->body_id;
    joint_def.bodyIdB = body_b->body_id;
    joint_def.collideConnected = true;
    this->joint_id = b2CreateWeldJoint(body_a->world.lock()->world_id, &joint_def);

}

WeldJoint::~WeldJoint() {
    this->destroy();
}

void WeldJoint::destroy() {
    if (!b2Joint_IsValid(this->joint_id)) {
        return;
    }
    b2DestroyJoint(joint_id);
    std::cout << "WeldJoint destroyed" << '\n';
}

