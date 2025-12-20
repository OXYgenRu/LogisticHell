//
// Created by EgorRychkov on 10.11.2025.
//

#include "PlayerSystem.h"
#include "Player.h"
#include "../World/GameWorld.h"

void PlayerInputListeners::set_main_listener(const unsigned int &id) {
    this->main_listener = id;
}

void PlayerInputListeners::set_intercepting_listener(const unsigned int &id) {
    this->intercepting_listener = id;
}

void PlayerInputListeners::set_background_main_listener(const unsigned int &id) {
    this->background_main_listener = id;
}

void PlayerInputListeners::set_background_intercepting_listener(const unsigned int &id) {
    this->background_intercepting_listener = id;
}


std::optional<unsigned int> PlayerInputListeners::get_main_listener() {
    return this->main_listener;
}

std::optional<unsigned int> PlayerInputListeners::get_intercepting_listener() {
    return this->intercepting_listener;
}

std::optional<unsigned int> PlayerInputListeners::get_background_main_listener() {
    return this->background_main_listener;
}

std::optional<unsigned int> PlayerInputListeners::get_background_intercepting_listener() {
    return this->background_intercepting_listener;
}


std::shared_ptr<PlayerSystem>
PlayerSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                     const std::string &node_id,
                     int render_priority) {
    auto node = std::make_shared<PlayerSystem>(parent, node_id, render_priority);
    PlayerSystem::setup(node, world);
    parent->add_node(node);
    return node;
}

void PlayerSystem::setup(const std::shared_ptr<PlayerSystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

std::shared_ptr<Player> PlayerSystem::create_player(const std::string &name) {
    unsigned int new_id = this->max_player_id++;
    this->players[new_id] = Player::create(world.lock(), new_id, world.lock(), "Player:" + name);
    this->input_listeners[new_id] = std::make_shared<PlayerInputListeners>(new_id);
    return this->players[new_id];
}

std::shared_ptr<PlayerInputListeners> PlayerSystem::get_player_listeners(const unsigned int &player_id) {
    auto it = this->input_listeners.find(player_id);
    if (it == this->input_listeners.end()) {
        return nullptr;
    }
    return it->second;
}