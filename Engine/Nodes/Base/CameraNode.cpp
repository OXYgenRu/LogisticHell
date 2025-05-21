//
// Created by EgorRychkov on 17.04.2025.
//

#include "CameraNode.h"
#include "../../Application.h"
#include "../Control/CameraController.h"

std::shared_ptr<CameraNode>
CameraNode::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, int render_priority,
                   int render_priority_layers) {
    auto node = std::make_shared<CameraNode>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    parent->add_node(node);
    node->zoom = 1;
    node->set_zoom(2);
    node->set_camera_target({100, 100});
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