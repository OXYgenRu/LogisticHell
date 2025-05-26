//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_GRIDCELL_H
#define LOGISTICHELL_GRIDCELL_H

#include "../../../../../Engine/Nodes/Base/Node.h"
#include "../../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class Structure;

class Grid;

class GridCell : public Node {
public:
    static std::shared_ptr<GridCell>
    create(const std::shared_ptr<Node> &parent, std::shared_ptr<Structure> structure, std::shared_ptr<Grid> grid,
           sf::Vector2i grid_position, float cell_size,
           int render_priority = 0);


    explicit GridCell(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(std::shared_ptr<GridCell> node, std::shared_ptr<Structure> structure, std::shared_ptr<Grid> grid,
          sf::Vector2i grid_position,
          float cell_size);

    std::vector<sf::Vector2f> vertices;
    std::weak_ptr<Structure> structure;
    std::shared_ptr<TexturedQuad> textured_quad;
};


#endif //LOGISTICHELL_GRIDCELL_H
