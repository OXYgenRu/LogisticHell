//
// Created by EgorRychkov on 30.04.2025.
//

#ifndef LOGISTICHELL_COMPONENTGRID_H
#define LOGISTICHELL_COMPONENTGRID_H


#include "../../../../../Engine/Nodes/Base/Node.h"

class GridCell;

class Component;

class ComponentGrid : public Node {
public:
    static std::shared_ptr<ComponentGrid>
    create(const std::shared_ptr<Node> &parent, std::shared_ptr<Component> component,
           int render_priority = 0);


    explicit ComponentGrid(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void setup(std::shared_ptr<ComponentGrid> node, std::shared_ptr<Component> component);

    std::weak_ptr<Component> component;

    std::vector<std::vector<std::shared_ptr<GridCell>>> grid_cells;
};


#endif //LOGISTICHELL_COMPONENTGRID_H
