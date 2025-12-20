//
// Created by EgorRychkov on 14.12.2025.
//

#include "PlayersApi.h"
#include "../../World/GameWorld.h"

PlayersApi::PlayersApi(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}

unsigned int PlayersApi::create_player(const std::string &name) {
    return world.lock()->get_player_system()->create_player(name)->get_id();
}

void PlayersApi::set_main_listener(const unsigned int &player_id, const unsigned int &listener_id) {
    world.lock()->get_player_system()->get_player_listeners(player_id)->set_main_listener(listener_id);
}