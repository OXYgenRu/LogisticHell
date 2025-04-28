//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_COLLISIONPOLYGON_H
#define LOGISTICHELL_COLLISIONPOLYGON_H

#include "../Base/ContentNode.h"
#include "RigidBody.h"

class CollisionPolygon : public ContentNode {
public:
    static std::shared_ptr<CollisionPolygon>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<RigidBody> rigid_body, b2ShapeDef &shape_def,
           b2Polygon &polygon,
           int render_priority = 0);

    explicit CollisionPolygon(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                            render_priority) {}

    b2ShapeDef shape_def;
    b2Polygon polygon;
    b2BodyId rigid_body_id;
    std::weak_ptr<RigidBody> rigid_body;
};


#endif //LOGISTICHELL_COLLISIONPOLYGON_H
