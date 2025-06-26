//
// Created by EgorRychkov on 21.06.2025.
//

#ifndef LOGISTICHELL_STRUCTURESSYSTEM_H
#define LOGISTICHELL_STRUCTURESSYSTEM_H

#include "vector"
#include "memory"
#include "Structure.h"

class MainScene;

class StructuresSystem {
public:
    explicit StructuresSystem(const std::shared_ptr<MainScene> &scene, float block_side_size);

    void create_structure(std::shared_ptr<Blueprint> &blueprint, const sf::Vector2f &dock_position, EngineContext &ctx);

    std::vector<std::shared_ptr<Structure>> structures;
    std::weak_ptr<MainScene> scene;
    float block_side_size;

};


#endif //LOGISTICHELL_STRUCTURESSYSTEM_H
