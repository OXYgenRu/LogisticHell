//
// Created by EgorRychkov on 21.11.2025.
//

#include "ListenersApi.h"
#include "../../World/GameWorld.h"

ListenersApi::ListenersApi(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}


unsigned int ListenersApi::register_listener(const std::shared_ptr<InputListener> &listener) {
    return world.lock()->get_input_listeners_system()->register_listener(listener);
}

void ListenersApi::add_observer(const unsigned int &listener_id, const unsigned int &observer_id) {
    std::shared_ptr<InputListener> listener = world.lock()->get_input_listeners_system()->get_listener(listener_id);
    if (listener == nullptr) {
        throw std::runtime_error("Api:Listeners: listener not found by id:" + std::to_string(listener_id));
    }
    listener->add_observer(observer_id);
}

void ListenersApi::delete_observer(const unsigned int &listener_id, const unsigned int &observer_id) {
    std::shared_ptr<InputListener> listener = world.lock()->get_input_listeners_system()->get_listener(listener_id);
    if (listener == nullptr) {
        throw std::runtime_error("Api:Listeners: listener not found by id:" + std::to_string(listener_id));
    }
    listener->delete_observer(observer_id);
}