//
// Created by EgorRychkov on 28.07.2025.
//

#include "UnitsBehaviorStorage.h"


void
UnitsBehaviorStorage::set_unit_behavior(const unsigned int &unit_index, const std::shared_ptr<UnitBehavior> &behavior) {
    this->units[unit_index] = behavior;
}

std::shared_ptr<UnitBehavior> &UnitsBehaviorStorage::get_unit_behavior(const unsigned int &unit_index) {
    auto it = this->units.find(unit_index);
    if (it == units.end()) {
        throw std::runtime_error("Unit behavior not found by unit index");
    }
    return it->second;
}