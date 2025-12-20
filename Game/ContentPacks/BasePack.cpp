//
// Created by EgorRychkov on 14.12.2025.
//

#include "BasePack.h"
#include "../MainScene/Scripting/Api/Api.h"
#include "../MainScene/Player/InputListenersSystem.h"
#include "../MainScene/Scripting/UnitsBehaviorStorage.h"
#include <iostream>


class TestWPusherInput : public InputListener {
public:
    void while_key_pressed(const unsigned int &observer, const sf::Keyboard::Key &key, Api &api) override {
        if (key != sf::Keyboard::Key::W) {
            return;
        }
        api.units->apply_local_force(observer, {0, 0}, {0, 0}, {0, 1000});
    }
};

class TestWPusher : public UnitBehavior {
public:
    void on_spawn(const unsigned int &unit_id, Api &api) override {
        if (api.values_storage->get("base_pack", "pusher_listener_id").has_value()) {
            unsigned int listener_id = api.values_storage->get("base_pack",
                                                               "pusher_listener_id").value().as<unsigned int>();
            api.listeners->add_observer(listener_id, unit_id);
        }

    }

    void on_destroy(const unsigned int &unit_id, Api &api) override {
        if (api.values_storage->get("base_pack", "pusher_listener_id").has_value()) {
            unsigned int listener_id = api.values_storage->get("base_pack",
                                                               "pusher_listener_id").value().as<unsigned int>();
            api.listeners->delete_observer(listener_id, unit_id);
        }
    }
};

std::vector<ContentPacks::Dependence> BasePack::get_dependencies() {
    return {};
}

void BasePack::on_world_open(Api &api) {
    player_id = api.player->create_player("Test");
    input_listener_id = api.listeners->register_listener(std::make_shared<TestWPusherInput>());
    api.player->set_main_listener(player_id, input_listener_id);
    api.values_storage->set("base_pack", "pusher_listener_id", Scripting::Value(input_listener_id));
    api.units->set_unit_behavior(api.units->get_unit_index("test_w_pusher"), std::make_shared<TestWPusher>());
}