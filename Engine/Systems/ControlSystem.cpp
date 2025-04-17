//
// Created by EgorRychkov on 17.04.2025.
//

#include "ControlSystem.h"
#include "../Application.h"
#include "../Nodes/Control/Controller.h"

void ControlSystem::update(EngineContext &ctx) {


    for (int i = 0; i < ctx.app->tree->get_free_tree_index(); i++) {
        if (!ctx.app->tree->get_active_update_indices()[i]) {
            continue;
        }
        if (ctx.app->tree->get_flatten_tree()[i]->get_node_type() == 5) {
            auto node = std::static_pointer_cast<Controller>(ctx.app->tree->get_flatten_tree()[i]);
            for (sf::Event &event: this->control_events) {
                if (event.type == sf::Event::KeyPressed) {
                    node->on_key_press(event);
                    std::cout << this->control_events.size() << '\n';
                }
                if (event.type == sf::Event::KeyReleased) {
                    node->on_key_release(event);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    node->on_mouse_press(event);
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    node->on_mouse_release(event);
                }
                if (event.type == sf::Event::MouseMoved) {
                    node->on_mouse_moved(event);
                }
                if (event.type == sf::Event::MouseWheelScrolled) {
                    node->on_mouse_wheel_scrolled(event);
                }
            }
        }
    }
    for (int i = 0; i < this->control_events.size(); i++) {
        this->control_events.pop_back();
    }
    ctx.app->tree->get_active_update_indices();
}

void ControlSystem::collect_event(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::KeyReleased) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseMoved) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseWheelScrolled) {
        this->control_events.push_back(event);
    }
}