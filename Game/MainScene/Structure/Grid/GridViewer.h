//
// Created by EgorRychkov on 28.04.2025.
//

#ifndef LOGISTICHELL_GRIDVIEWER_H
#define LOGISTICHELL_GRIDVIEWER_H


#include <box2d/math_functions.h>
#include "../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"
#include "Grid.h"


class GridViewer : public TexturedQuad {
public:
    static std::shared_ptr<GridViewer>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Grid> grid, b2Vec2 grid_position, float cell_size,
           int render_priority = 0);


    explicit GridViewer(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : TexturedQuad(parent, render_priority) {}

    static void
    setup(std::shared_ptr<GridViewer> node, std::shared_ptr<Grid> grid, b2Vec2 grid_position, float cell_size);

    void update(EngineContext &ctx) override;

    b2Vec2 vertices[4];
    std::weak_ptr<Grid> grid;
};


#endif //LOGISTICHELL_GRIDVIEWER_H
