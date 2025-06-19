//
// Created by EgorRychkov on 17.06.2025.
//

#ifndef LOGISTICHELL_REVOLUTEJOINT_H
#define LOGISTICHELL_REVOLUTEJOINT_H

#include "memory"
#include "box2d/box2d.h"

class RigidBody;

class RevoluteJoint {
public:
    RevoluteJoint(const std::shared_ptr<RigidBody> &body_a, const std::shared_ptr<RigidBody> &body_b,
                  b2RevoluteJointDef &joint_def);

    ~RevoluteJoint();

    void destroy();

private:
    b2JointId joint_id;
    std::weak_ptr<RigidBody> body_a, body_b;
};


#endif //LOGISTICHELL_REVOLUTEJOINT_H
