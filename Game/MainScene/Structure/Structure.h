//
// Created by EgorRychkov on 19.06.2025.
//

#ifndef LOGISTICHELL_STRUCTURE_H
#define LOGISTICHELL_STRUCTURE_H

#include "vector"
#include "memory"
#include "Unit.h"
#include "Component.h"
#include "../Blueprints/Blueprint/Blueprint.h"

class Structure {
private:
    unsigned int structure_id;
public:
    Structure(const std::shared_ptr<Blueprint> &blueprint, const unsigned int &structure_id);

    ~Structure();

    const unsigned int &get_structure_id();

    void delete_component(const std::shared_ptr<Component> &component);

    void delete_unit(const std::shared_ptr<Unit> &unit);

    std::vector<std::shared_ptr<Unit>> units;
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<Blueprint> blueprint;
};


#endif //LOGISTICHELL_STRUCTURE_H
