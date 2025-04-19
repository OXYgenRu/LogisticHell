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
    node->view_point = sf::View(
            sf::FloatRect(0, 0, float(ctx.app->video_mode.width), float(ctx.app->video_mode.height)));
    node->view_point.setCenter(0, 0);
    node->view_point.zoom(1);
    node->zoom = 1;
    node->original_size = sf::Vector2f(float(ctx.app->video_mode.width), float(ctx.app->video_mode.height));
    node->camera_controller = CameraController::create(node, node, 0);
    return node;
}

void CameraNode::set_zoom(float new_zoom) {
    this->zoom = new_zoom;
    this->view_point.setSize(original_size);
    this->view_point.zoom(new_zoom);
}

void CameraNode::set_camera_target(sf::Vector2f camera_target) {
    this->view_point.setCenter(camera_target);
}

int CameraNode::get_node_type() const {
    return 6;
}

void CameraNode::render(EngineContext &ctx) {
    ctx.app->window->setView(this->view_point);
}

void CameraNode::rollback_view_point(EngineContext &ctx) {
    ctx.app->window->setView(ctx.app->standard_view);
}