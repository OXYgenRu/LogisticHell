//
// Created by EgorRychkov on 28.12.2025.
//

#include "LocalPlayer.h"
#include "../MainScene/Scripting/Api/Api.h"

std::vector<ContentPacks::Dependence> LocalPlayer::get_dependencies() {
    return {};
}

void LocalPlayer::on_world_open(Api &api) {
    api.values_storage->set(get_pack_name(), "player_id", api.player->create_player("LocalPlayer"));
}