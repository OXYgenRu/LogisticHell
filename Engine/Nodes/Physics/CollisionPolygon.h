//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_COLLISIONPOLYGON_H
#define LOGISTICHELL_COLLISIONPOLYGON_H

#include "RigidBody.h"
#include "../Base/Node.h"

class CollisionPolygon : public Node {
public:
    static std::shared_ptr<CollisionPolygon>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<RigidBody> &rigid_body,
           b2ShapeDef &shape_def,
           b2Polygon &polygon, const std::string &node_id,
           int render_priority = 0);

    explicit CollisionPolygon(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {}

    ~CollisionPolygon();

    void destroy();

    b2ShapeDef shape_def;
    b2Polygon polygon;
    b2ShapeId shape_id;
    std::weak_ptr<RigidBody> rigid_body;
};


#endif //LOGISTICHELL_COLLISIONPOLYGON_H
