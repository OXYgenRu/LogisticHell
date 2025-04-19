//
// Created by EgorRychkov on 19.04.2025.
//

#include "CameraController.h"
#include "../Base/ContainerNode.h"
#include "../../Application.h"
#include "../Base/CameraNode.h"

std::shared_ptr<CameraController>
CameraController::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<CameraNode> camera,
                         int render_priority) {
    auto node = std::make_shared<CameraController>(parent, render_priority);
    parent->add_node(node);
    node->start_mouse_pos = sf::Vector2f(0, 0);
    node->camera = camera;
    return node;
}

void CameraController::render(EngineContext &ctx) {

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
        this->camera->view_point.move(-delta * this->camera->zoom);
    }
}

void CameraController::on_mouse_wheel_scrolled(sf::Event &event, EngineContext &ctx) {
    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
        float delta = event.mouseWheelScroll.delta;
        if (delta > 0) {
            this->camera->set_zoom(float(this->camera->zoom * 0.7));
        } else {
            this->camera->set_zoom(float(this->camera->zoom / 0.7));
        }
    }
}