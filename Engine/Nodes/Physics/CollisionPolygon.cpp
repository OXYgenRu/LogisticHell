//
// Created by EgorRychkov on 26.04.2025.
//

#include "CollisionPolygon.h"
#include "box2d/box2d.h"

std::shared_ptr<CollisionPolygon>
CollisionPolygon::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<RigidBody> &rigid_body,
                         b2ShapeDef &shape_def, b2Polygon &polygon, const std::string &node_id,
                         int render_priority) {
    auto node = std::make_shared<CollisionPolygon>(parent, node_id, render_priority);
    node->shape_def = shape_def;
    node->polygon = polygon;
    node->rigid_body = rigid_body;
    node->shape_id = b2CreatePolygonShape(rigid_body->body_id, &node->shape_def, &node->polygon);
    parent->add_node(node);
    return node;
}


CollisionPolygon::~CollisionPolygon() {
    this->destroy();
}

void CollisionPolygon::destroy() {
    if (!b2Shape_IsValid(this->shape_id)) {
        return;
    }
    b2DestroyShape(this->shape_id, true);
    std::cout << "Shape destroyed" << '\n';
}