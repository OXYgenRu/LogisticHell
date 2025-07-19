//
// Created by EgorRychkov on 19.04.2025.
//

#include "CameraController.h"
#include "../../Application.h"
#include "../Base/CameraNode.h"

std::shared_ptr<CameraController>
CameraController::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<CameraNode> &camera,
                         const std::string &node_id,
                         int render_priority) {
    auto node = std::make_shared<CameraController>(parent, node_id, render_priority);
    parent->add_node(node);
    node->start_mouse_pos = sf::Vector2f(0, 0);
    node->camera = camera;
    return node;
}

void CameraController::render(EngineContext &ctx, sf::RenderStates &states) {

}

void CameraController::update(EngineContext &ctx) {

}

int CameraController::get_node_type() const {
    return 7;
}

void CameraController::on_mouse_press(sf::Event &event, EngineContext &ctx) {
    if (event.mouseButton.button == sf::Mouse::Middle) {
        this->wheel_pressed = true;
        start_mouse_pos = ctx.app->window->mapPixelToCoords(sf::Mouse::getPosition(*ctx.app->window));
    }
}

void CameraController::on_mouse_release(sf::Event &event, EngineContext &ctx) {
    if (event.mouseButton.button == sf::Mouse::Middle) {
        this->wheel_pressed = false;
    }
}


void CameraController::on_mouse_moved(sf::Event &event, EngineContext &ctx) {
    if (this->wheel_pressed) {
        sf::Vector2f current_mouse_pos = ctx.app->window->mapPixelToCoords(sf::Mouse::getPosition(*ctx.app->window));
        sf::Vector2f delta = current_mouse_pos - this->start_mouse_pos;
        this->start_mouse_pos = current_mouse_pos;
        this->camera.lock()->get_transformable().setPosition(
                (-delta * this->camera.lock()->zoom) + this->camera.lock()->get_transformable().getPosition());
    }
}

void CameraController::on_mouse_wheel_scrolled(sf::Event &event, EngineContext &ctx) {
    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
        float delta = event.mouseWheelScroll.delta;
        if (delta > 0) {
            this->camera.lock()->set_zoom(float(this->camera.lock()->zoom * 0.7));
        } else {
            this->camera.lock()->set_zoom(float(this->camera.lock()->zoom / 0.7));
        }
    }
}