//
// Created by EgorRychkov on 17.04.2025.
//

#include "CameraNode.h"
#include "../../Application.h"
#include "../Control/CameraController.h"

std::shared_ptr<CameraNode>
CameraNode::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, int render_priority) {
    auto node = std::make_shared<CameraNode>(parent, render_priority);
    parent->add_node(node);
    node->zoom = 1;
    node->set_zoom(1);
    node->camera_controller = CameraController::create(node, node, 0);
    return node;
}

void CameraNode::set_zoom(float new_zoom) {
    this->zoom = new_zoom;
    this->transform.setScale(new_zoom, new_zoom);
}

void CameraNode::set_camera_target(sf::Vector2f camera_target) {
    this->transform.setPosition(camera_target);
}

int CameraNode::get_node_type() const {
    return 6;
}

const sf::Transform &CameraNode::get_transform() {
    return this->transform.getInverseTransform();
}

void CameraNode::set_locked(bool is_locked) {
    this->locked = is_locked;
    this->camera_controller->set_update_flag(!is_locked);
}