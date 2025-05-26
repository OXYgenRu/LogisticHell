//
// Created by EgorRychkov on 16.04.2025.
//

#include "Controller.h"
#include "../Base/Node.h"

std::shared_ptr<Controller> Controller::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<Controller>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void Controller::render(EngineContext &ctx, sf::RenderStates &states) {

}

void Controller::update(EngineContext &ctx) {

}

int Controller::get_node_type() const {
    return 5;
}

void Controller::on_key_press(sf::Event &event, EngineContext &ctx) {}

void Controller::on_key_release(sf::Event &event, EngineContext &ctx) {}

void Controller::on_mouse_press(sf::Event &event, EngineContext &ctx) {}

void Controller::on_mouse_release(sf::Event &event, EngineContext &ctx) {}

void Controller::on_mouse_moved(sf::Event &event, EngineContext &ctx) {}

void Controller::on_mouse_wheel_scrolled(sf::Event &event, EngineContext &ctx) {}