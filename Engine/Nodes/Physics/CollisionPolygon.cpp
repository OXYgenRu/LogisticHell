//
// Created by EgorRychkov on 26.04.2025.
//

#include "CollisionPolygon.h"
#include "../Base/ContainerNode.h"

std::shared_ptr<CollisionPolygon>
CollisionPolygon::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<RigidBody> rigid_body,
                         b2ShapeDef &shape_def, b2Polygon &polygon,
                         int render_priority) {
    auto node = std::make_shared<CollisionPolygon>(parent, render_priority);
    node->shape_def = shape_def;
    node->polygon = polygon;
    node->rigid_body = rigid_body->body;
    b2CreatePolygonShape(rigid_body->body, &node->shape_def, &node->polygon);
    parent->add_node(node);
    return node;
}

