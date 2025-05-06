//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_DOCK_H
#define LOGISTICHELL_DOCK_H


#include "../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/Render/Shapes/Text.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "GridCollider/DockGridCollider.h"
#include "Controller/DockController.h"
#include "BuildingGrid/BuildingGrid.h"
#include "Builder/Builder.h"

class Structure;

class Dock : public ContainerNode {
public:
    static std::shared_ptr<Dock>
    create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<World> world,
           sf::Vector2f position,
           sf::Vector2i grid_size, float b2_cell_size,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit Dock(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void
    setup(std::shared_ptr<Dock> node, EngineContext &ctx, std::shared_ptr<World> world, sf::Vector2f position,
          sf::Vector2i grid_size, float b2_cell_size);


    std::shared_ptr<Builder> builder;
    std::shared_ptr<BuildingGrid> building_grid;

    std::shared_ptr<DockController> controller;
    std::shared_ptr<ContainerNode> panel;
    std::shared_ptr<DockGridCollider> dock_collider;
    std::shared_ptr<CameraNode> camera;

    std::weak_ptr<World> world;
};


#endif //LOGISTICHELL_DOCK_H
