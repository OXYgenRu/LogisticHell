//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_DOCK_H
#define LOGISTICHELL_DOCK_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/Render/Shapes/Text.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "EditorController/DockController.h"
#include "BuildingGrid/BuildingGrid.h"
#include "Builder/Builder.h"
#include "EditorInterface/EditorInterface.h"
#include "EditorController/EditorController.h"

class Structure;

class Dock : public Node {
public:
    static std::shared_ptr<Dock>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const  std::shared_ptr<World>& world,
           sf::Vector2f position,
           sf::Vector2i grid_size, float b2_cell_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader,
           const std::shared_ptr<BlockFactory> &block_factory,
           int render_priority = 0);


    explicit Dock(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(const std::shared_ptr<Dock> &node, EngineContext &ctx,const  std::shared_ptr<World> &world, sf::Vector2f position,
          sf::Vector2i grid_size, float b2_cell_size, const  std::shared_ptr<BlueprintLoader> &blueprint_loader,
          const std::shared_ptr<BlockFactory> &block_factory);

    std::shared_ptr<UI::Collider> background_collider;
    std::shared_ptr<EditorController> editor_controller;
    std::shared_ptr<BuildingGrid> building_grid;
    std::shared_ptr<DockController> controller;
    std::shared_ptr<EditorInterface> interface;
    std::shared_ptr<CameraNode> camera;
    std::weak_ptr<World> world;
};


#endif //LOGISTICHELL_DOCK_H
