//
// Created by EgorRychkov on 30.04.2025.
//

#ifndef LOGISTICHELL_COMPONENTGRID_H
#define LOGISTICHELL_COMPONENTGRID_H


#include "../../../../../Engine/Nodes/Base/ContainerNode.h"

class GridCell;

class Component;

class ComponentGrid : public ContainerNode {
public:
    static std::shared_ptr<ComponentGrid>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Component> component,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit ComponentGrid(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void setup(std::shared_ptr<ComponentGrid> node, std::shared_ptr<Component> component);

    std::weak_ptr<Component> component;

    std::vector<std::vector<std::shared_ptr<GridCell>>> grid_cells;
};


#endif //LOGISTICHELL_COMPONENTGRID_H
