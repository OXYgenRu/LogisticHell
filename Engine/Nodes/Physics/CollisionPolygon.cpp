//
// Created by EgorRychkov on 26.04.2025.
//

#include "CollisionPolygon.h"

std::shared_ptr<CollisionPolygon>
CollisionPolygon::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<RigidBody> &rigid_body,
                         b2ShapeDef &shape_def, b2Polygon &polygon,
                         int render_priority) {
    auto node = std::make_shared<CollisionPolygon>(parent, render_priority);
    node->shape_def = shape_def;
    node->polygon = polygon;
    node->rigid_body_id = rigid_body->body;
    node->rigid_body = rigid_body;
    b2CreatePolygonShape(rigid_body->body, &node->shape_def, &node->polygon);
    parent->add_node(node);
    return node;
}

