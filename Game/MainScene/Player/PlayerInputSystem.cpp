//
// Created by EgorRychkov on 10.11.2025.
//

#include "PlayerInputSystem.h"
#include "PlayerSystem.h"
#include "../World/GameWorld.h"
#include "InputListenersSystem.h"

std::shared_ptr<PlayerInputSystem>
PlayerInputSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                          const std::string &node_id,
                          int render_priority) {
    auto node = std::make_shared<PlayerInputSystem>(parent, node_id, render_priority);
    PlayerInputSystem::setup(node, world);
    parent->add_node(node);
    return node;
}

void PlayerInputSystem::setup(const std::shared_ptr<PlayerInputSystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

std::pair<
        std::optional<std::shared_ptr<InputListener>>,
        std::optional<std::shared_ptr<InputListener>>>
PlayerInputSystem::get_player_listeners(const unsigned int &player_id) {
    std::shared_ptr<PlayerInputListeners> listeners = world.lock()->get_player_system()->get_player_listeners(
            player_id);
    if (listeners == nullptr) {
        return {std::nullopt, std::nullopt};
    }
    std::shared_ptr<InputListener> interception_listener = world.lock()->get_input_listeners_system()->get_listener(
            listeners->get_intercepting_listener());
    if (interception_listener != nullptr) {
        std::shared_ptr<InputListener> background_listener = world.lock()->get_input_listeners_system()->get_listener(
                listeners->get_background_intercepting_listener());
        if (background_listener == nullptr) {
            return {interception_listener, std::nullopt};
        }
        return {interception_listener, background_listener};
    }
    std::shared_ptr<InputListener> main_listener = world.lock()->get_input_listeners_system()->get_listener(
            listeners->get_main_listener());
    if (main_listener == nullptr) {
        return {std::nullopt, std::nullopt};
    }
    std::shared_ptr<InputListener> background_listener = world.lock()->get_input_listeners_system()->get_listener(
            listeners->get_background_main_listener());
    if (background_listener == nullptr) {
        return {main_listener, std::nullopt};
    }
    return {main_listener, background_listener};
}

void PlayerInputSystem::handle_key_press(const unsigned int &player_id, const sf::Keyboard::Key &key) {
    auto listeners = get_player_listeners(player_id);
    if (listeners.first.has_value()) {
        world.lock()->get_input_listeners_system()->on_key_press(listeners.first.value(), key);
    }
    if (listeners.second.has_value()) {
        world.lock()->get_input_listeners_system()->on_key_press(listeners.first.value(), key);
    }
}

void PlayerInputSystem::handle_key_release(const unsigned int &player_id, const sf::Keyboard::Key &key) {
    auto listeners = get_player_listeners(player_id);
    if (listeners.first.has_value()) {
        world.lock()->get_input_listeners_system()->on_key_release(listeners.first.value(), key);
    }
    if (listeners.second.has_value()) {
        world.lock()->get_input_listeners_system()->on_key_release(listeners.first.value(), key);
    }
}

void PlayerInputSystem::handle_while_key_pressed(const unsigned int &player_id, const sf::Keyboard::Key &key) {
    auto listeners = get_player_listeners(player_id);
    if (listeners.first.has_value()) {
        world.lock()->get_input_listeners_system()->while_key_pressed(listeners.first.value(), key);
    }
    if (listeners.second.has_value()) {
        world.lock()->get_input_listeners_system()->while_key_pressed(listeners.first.value(), key);
    }
}