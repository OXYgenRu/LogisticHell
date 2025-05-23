//
// Created by EgorRychkov on 28.04.2025.
//

#ifndef LOGISTICHELL_GRID_H
#define LOGISTICHELL_GRID_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "box2d/box2d.h"
#include "../Block/BaseBlock.h"
#include "GridCell/GridCell.h"

class GridViewer;

class Structure;


class Grid : public ContainerNode {
public:
    static std::shared_ptr<Grid>
    create(std::shared_ptr<ContainerNode> parent, sf::Vector2i grid_size, float cell_size,
           std::shared_ptr<Structure> structure,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit Grid(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void
    setup(std::shared_ptr<Grid> node, sf::Vector2i grid_size, float cell_size, std::shared_ptr<Structure> &structure);


    std::vector<std::vector<std::shared_ptr<GridCell>>> grid_cells;
    std::shared_ptr<ContainerNode> grid_view_layer;
    std::weak_ptr<Structure> structure;
    sf::Vector2i grid_size;
    float cell_size;
};


#endif //LOGISTICHELL_GRID_H
