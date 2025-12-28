//
// Created by EgorRychkov on 28.12.2025.
//

#include "PlayerEntity.h"
#include "../MainScene/Scripting/Api/Api.h"


std::vector<ContentPacks::Dependence> PlayerEntity::get_dependencies() {
    return {ContentPacks::Dependence("LocalPlayer", ContentPacks::DependenceType::Hard)};
}

void PlayerEntity::on_world_open(Api &api) {
    api.values_storage->set(get_pack_name(), "player_id", api.player->create_player("LocalPlayer"));
}