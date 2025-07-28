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