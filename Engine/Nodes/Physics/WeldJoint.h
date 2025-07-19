//
// Created by EgorRychkov on 03.07.2025.
//

#ifndef LOGISTICHELL_WELDJOINT_H
#define LOGISTICHELL_WELDJOINT_H


#include "../Base/Node.h"
#include "RigidBody.h"

class WeldJoint {
public:
    WeldJoint(const std::shared_ptr<RigidBody> &body_a,
              const std::shared_ptr<RigidBody> &body_b,
              b2WeldJointDef &joint_def);

    ~WeldJoint();

    void destroy();

private:
    b2JointId joint_id;
    std::weak_ptr<RigidBody> body_a, body_b;
};


#endif //LOGISTICHELL_WELDJOINT_H
