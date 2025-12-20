//
// Created by EgorRychkov on 15.12.2025.
//

#include "ValuesStorageApi.h"
#include "../../World/GameWorld.h"

ValuesStorageApi::ValuesStorageApi(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}

bool ValuesStorageApi::set(const std::string &namespace_, const std::string &name,Scripting::Value value) {
    return world.lock()->get_values_global_storage()->set(namespace_, name, value);
}

std::optional<Scripting::Value> ValuesStorageApi::get(const std::string &namespace_, const std::string &name) const {
    return world.lock()->get_values_global_storage()->get(namespace_, name);
}