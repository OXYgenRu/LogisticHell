//
// Created by EgorRychkov on 29.04.2025.
//

#ifndef LOGISTICHELL_GRIDCOLLIDER_H
#define LOGISTICHELL_GRIDCOLLIDER_H


#include "../../../../../Engine/Nodes/UI/UICollider.h"
#include "box2d/box2d.h"

class Grid;

class GridCollider : public UICollider {
public:
    static std::shared_ptr<GridCollider>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Grid> grid, int render_priority = 0);

    explicit GridCollider(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : UICollider(parent,
                                                                                                       render_priority) {}

    static void setup(std::shared_ptr<GridCollider> node, std::shared_ptr<Grid> grid);

    void on_mouse_release(sf::Event &event, EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::weak_ptr<Grid> grid;

    b2Vec2 b2_vertices[4];
};


#endif //LOGISTICHELL_GRIDCOLLIDER_H
