//
// Created by EgorRychkov on 16.06.2025.
//

#ifndef LOGISTICHELL_UNIT_H
#define LOGISTICHELL_UNIT_H

#include "iostream"
#include "unordered_map"
#include "UnitRenderQuad.h"
#include "memory"
#include "ComponentBlock.h"
#include "../Blueprints/UnitProperties/UnitProperties.h"

class Unit {
public:

private:
    std::shared_ptr<UnitBehavior> unit_behavior;
    std::vector<std::shared_ptr<ComponentBlock>> blocks;
    std::unordered_map<std::string, std::shared_ptr<UnitRenderQuad>> render_features;
};


#endif //LOGISTICHELL_UNIT_H
