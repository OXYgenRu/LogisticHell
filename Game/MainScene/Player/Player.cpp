//
// Created by EgorRychkov on 10.11.2025.
//

#include "Player.h"
#include "../World/GameWorld.h"

std::shared_ptr<PlayerInput>
PlayerInput::create(const std::shared_ptr<Node> &parent, const unsigned int &player_id,
                    const std::shared_ptr<GameWorld> &world,
                    const std::string &node_id, int render_priority) {
    auto node = std::make_shared<PlayerInput>(parent, node_id, render_priority);
    PlayerInput::setup(node, player_id, world);
    parent->add_node(node);
    return node;
}

void PlayerInput::setup(const std::shared_ptr<PlayerInput> &node, const unsigned int &player_id,
                        const std::shared_ptr<GameWorld> &world) {
    node->player_id = player_id;
    node->world = world;
}

void PlayerInput::on_key_press(sf::Event &event, EngineContext &ctx) {
    this->key_pressed[event.key.code] = true;
    world.lock()->get_player_input_system()->handle_key_press(player_id, event.key.code);
}

void PlayerInput::on_key_release(sf::Event &event, EngineContext &ctx) {
    this->key_pressed.erase(event.key.code);
    world.lock()->get_player_input_system()->handle_key_release(player_id, event.key.code);
}

void PlayerInput::update(EngineContext &ctx) {
    for (auto &to: key_pressed) {
        world.lock()->get_player_input_system()->handle_while_key_pressed(player_id, to.first);
    }
}


std::shared_ptr<Player>
Player::create(const std::shared_ptr<Node> &parent, const unsigned int &player_id,
               const std::shared_ptr<GameWorld> &world, const std::string &node_id,
               int render_priority) {
    auto node = std::make_shared<Player>(parent, node_id, render_priority);
    Player::setup(node, player_id, world);
    parent->add_node(node);
    return node;
}

void Player::setup(const std::shared_ptr<Player> &node, const unsigned int &player_id,
                   const std::shared_ptr<GameWorld> &world) {
    node->player_id = player_id;
    node->player_input = PlayerInput::create(node, player_id, world, "PlayerInput: " + std::to_string(player_id));
    node->world = world;
}

const unsigned int &Player::get_id() {
    return this->player_id;
}