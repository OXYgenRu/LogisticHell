//
// Created by EgorRychkov on 28.04.2025.
//

#ifndef LOGISTICHELL_STRUCTURE_H
#define LOGISTICHELL_STRUCTURE_H


#include "../../../Engine/Nodes/Physics/RigidBody.h"
#include "Grid/Grid.h"
#include "Component/Component.h"


class Structure : public Node {
public:
    static std::shared_ptr<Structure>
    create(const std::shared_ptr<Node> &parent, std::shared_ptr<World> world, sf::Vector2f position,
           sf::Vector2i grid_size, float cell_size,
           int render_priority = 0);


    explicit Structure(std::shared_ptr<Node> parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(std::shared_ptr<Structure> node, std::shared_ptr<World> world, sf::Vector2f position,
          sf::Vector2i grid_size, float cell_size);



    std::shared_ptr<Grid> grid;
    sf::Vector2f position;
    std::weak_ptr<World> world;
    std::vector<std::shared_ptr<Component>> components;

};

#endif //LOGISTICHELL_STRUCTURE_H
