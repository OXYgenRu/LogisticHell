//
// Created by EgorRychkov on 03.01.2026.
//

#include "JointPack.h"
#include "../MainScene/Scripting/Api/Api.h"
#include "../MainScene/Scripting/UnitsBehaviorStorage.h"

std::vector<ContentPacks::Dependence> JointPack::get_dependencies() {
    return {};
}

void JointPack::on_world_open(Api &api) {
    api.units->set_unit_behavior(api.units->get_unit_index(get_pack_name() + ":joint"),
                                 std::make_shared<UnitBehavior>());
}