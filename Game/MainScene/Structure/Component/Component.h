//
// Created by EgorRychkov on 30.04.2025.
//

#ifndef LOGISTICHELL_COMPONENT_H
#define LOGISTICHELL_COMPONENT_H


#include "../../../../Engine/Nodes/Physics/RigidBody.h"
#include "Grid/ComponentGrid.h"

class Structure;

class Component : public Node {
public:
    static std::shared_ptr<Component>
    create(const std::shared_ptr<Node> &parent, std::shared_ptr<Structure> structure,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit Component(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void setup(std::shared_ptr<Component> node, std::shared_ptr<Structure> structure);

    std::weak_ptr<Structure> structure;

    std::shared_ptr<ComponentGrid> grid;

    std::shared_ptr<RigidBody> body;
};


#endif //LOGISTICHELL_COMPONENT_H
