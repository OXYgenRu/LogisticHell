//
// Created by EgorRychkov on 16.04.2025.
//

#include "Controller.h"
#include "../Base/Node.h"

std::shared_ptr<Controller>
Controller::create(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority) {
    auto node = std::make_shared<Controller>(parent, node_id, render_priority);
    parent->add_node(node);
    return node;
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