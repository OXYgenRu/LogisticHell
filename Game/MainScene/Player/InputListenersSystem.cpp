//
// Created by EgorRychkov on 10.11.2025.
//

#include "InputListenersSystem.h"
#include "../World/GameWorld.h"


void InputListener::add_observer(const unsigned int &observer_id) {
    if (std::find(this->listener_observers.begin(), this->listener_observers.end(), observer_id) ==
        this->listener_observers.end()) {
        listener_observers.push_back(observer_id);
    }
}

void InputListener::delete_observer(const unsigned int &observer_id) {
    auto it = std::find(this->listener_observers.begin(), this->listener_observers.end(), observer_id);
    if (it == this->listener_observers.end()) {
        throw std::runtime_error("InputListener: deleting observer_id not found");
    }
    this->listener_observers.erase(it);
}

const std::vector<unsigned int> &InputListener::get_observers() {
    return this->listener_observers;
}

std::shared_ptr<InputListenersSystem>
InputListenersSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                             const std::string &node_id,
                             int render_priority) {
    auto node = std::make_shared<InputListenersSystem>(parent, node_id, render_priority);
    InputListenersSystem::setup(node, world);
    parent->add_node(node);
    return node;
}

void InputListenersSystem::setup(const std::shared_ptr<InputListenersSystem> &node,
                                 const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

unsigned int InputListenersSystem::register_listener(const std::shared_ptr<InputListener> &listener) {
    if (this->max_listener_id == UINT32_MAX) {
        throw std::runtime_error("InputListenersSystem: No free ids for listeners");
    }
    unsigned int listener_id = ++this->max_listener_id;
    this->input_listeners[listener_id] = listener;
    return listener_id;
}

std::shared_ptr<InputListener> InputListenersSystem::get_listener(const std::optional<unsigned int> &id) {
    if (!id.has_value()) {
        return nullptr;
    }
    auto it = this->input_listeners.find(id.value());
    if (it == this->input_listeners.end()) {
        return nullptr;
    }
    return it->second;
}

void InputListenersSystem::on_key_press(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key) {
    for (const unsigned int &to: listener->get_observers()) {
        listener->on_key_press(to, key, *world.lock()->get_api());
    }
}

void
InputListenersSystem::on_key_release(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key) {
    for (const unsigned int &to: listener->get_observers()) {
        listener->on_key_release(to, key, *world.lock()->get_api());
    }
}

void
InputListenersSystem::while_key_pressed(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key) {
    for (const unsigned int &to: listener->get_observers()) {
        listener->while_key_pressed(to, key, *world.lock()->get_api());
    }
}