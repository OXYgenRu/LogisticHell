//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_DOCK_H
#define LOGISTICHELL_DOCK_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Render/Shapes/Text.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "EditorController/DockController.h"
#include "Builder/Builder.h"
#include "EditorInterface/EditorInterface.h"
#include "EditorController/EditorController.h"
#include "Builder/BuildingGrid.h"
#include "../Structure/StructuresSystem.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"


class Dock : public Node {
public:
    static std::shared_ptr<Dock>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<World> &world,
           const std::shared_ptr<CameraNode> &world_camera,
           const std::shared_ptr<StructuresSystem> &structures_system,
           sf::Vector2f position,
           sf::Vector2i grid_size, float b2_cell_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader,
           int render_priority = 0);


    explicit Dock(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(const std::shared_ptr<Dock> &node, EngineContext &ctx, const std::shared_ptr<World> &world,
          const std::shared_ptr<CameraNode> &world_camera,
          const std::shared_ptr<StructuresSystem> &structures_system,
          sf::Vector2f position,
          sf::Vector2i grid_size, float b2_cell_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader);

    sf::Vector2f position;
    std::shared_ptr<UI::Rectangle> background;
    std::shared_ptr<EditorController> editor_controller;
    std::shared_ptr<BuildingGrid> building_grid;
    std::shared_ptr<DockController> controller;
    std::shared_ptr<EditorInterface> interface;
    std::shared_ptr<CameraNode> camera;
    std::weak_ptr<StructuresSystem> structures_system;
    std::weak_ptr<World> world;
};

class DockSpawner : public Node {
private:
    sf::Vector2i grid_size;
    sf::Vector2f position;
    float b2_block_side_size;
    std::weak_ptr<MainScene> scene;
    std::shared_ptr<Dock> dock;
    std::shared_ptr<UI::Button> dock_area;
    std::shared_ptr<Text> text;
public:
    static std::shared_ptr<DockSpawner>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<MainScene> &scene,
           const sf::Vector2f &position, const sf::Vector2i &grid_size, float b2_block_side_size,
           int render_priority = 0);

    explicit DockSpawner(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent,
                                                                                              render_priority) {}

    static void
    setup(const std::shared_ptr<DockSpawner> &node, EngineContext &ctx, const std::shared_ptr<MainScene> &scene,
          const sf::Vector2f &position, const sf::Vector2i &grid_size, float b2_block_side_size);
};


#endif //LOGISTICHELL_DOCK_H
