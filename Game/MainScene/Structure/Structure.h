//
// Created by EgorRychkov on 28.04.2025.
//

#ifndef LOGISTICHELL_STRUCTURE_H
#define LOGISTICHELL_STRUCTURE_H


#include "../../../Engine/Nodes/Physics/RigidBody.h"
#include "Grid/Grid.h"

class Structure : public RigidBody {
public:
    static std::shared_ptr<Structure>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<World> world, b2BodyDef &body_def,
           sf::Vector2i grid_size, float cell_size,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit Structure(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : RigidBody(parent, render_priority) {}

    static void
    setup(std::shared_ptr<Structure> node, sf::Vector2i grid_size, float cell_size);

    std::shared_ptr<Grid> grid;
};


#endif //LOGISTICHELL_STRUCTURE_H
