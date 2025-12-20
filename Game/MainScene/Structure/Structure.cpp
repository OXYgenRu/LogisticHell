//
// Created by EgorRychkov on 19.06.2025.
//

#include "Structure.h"

Structure::Structure(const std::shared_ptr<Blueprint> &blueprint, const unsigned int &structure_id) {
    this->blueprint = blueprint;
    this->structure_id = structure_id;
}

Structure::~Structure() {
    std::cout << "Structure destroyed" << '\n';
}

const unsigned int &Structure::get_structure_id() {
    return structure_id;
}


void Structure::delete_component(const std::shared_ptr<Component> &component) {
    auto it = std::find(this->components.begin(), this->components.end(), component);
    if (it == this->components.begin()) {
        return;
    }
    this->components.erase(it);
}

void Structure::delete_unit(const std::shared_ptr<Unit> &unit) {
    auto it = std::find(this->units.begin(), this->units.end(), unit);
    if (it == this->units.begin()) {
        return;
    }
    this->units.erase(it);
}