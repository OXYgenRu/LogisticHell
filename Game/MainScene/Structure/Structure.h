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
public:
    Structure(const std::shared_ptr<Blueprint> &blueprint);

    ~Structure();


    std::vector<std::shared_ptr<Unit>> units;
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<Blueprint> blueprint;
};


#endif //LOGISTICHELL_STRUCTURE_H
