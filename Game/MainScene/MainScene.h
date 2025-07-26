//
// Created by EgorRychkov on 27.04.2025.
//

#ifndef LOGISTICHELL_MAINSCENE_H
#define LOGISTICHELL_MAINSCENE_H


#include "../../Engine/Scene.h"
#include "../../Engine/Nodes/Base/CameraNode.h"
#include "../../Engine/Nodes/Physics/World.h"
#include "Dock/Dock.h"
#include "Structure/StructuresSystem.h"
#include "Dock/DocksSystem.h"
#include "../../Engine/Nodes/UI/Inspector.h"

class MainScene : public Scene {
public:
    static std::shared_ptr<MainScene> create(const std::string &node_id) {
        auto node = std::make_shared<MainScene>(node_id);
        return node;
    }

    explicit MainScene(const std::string &node_id) : Scene(node_id) {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<Inspector> inspector;
    std::shared_ptr<UI::Collider> background_collider;
    std::shared_ptr<CameraNode> world_camera;
    std::shared_ptr<World> world;
    std::shared_ptr<StructuresSystem> structures_system;
    std::shared_ptr<DocksSystem> docks_system;
    std::shared_ptr<BlueprintLoader> blueprint_loader;
};


#endif //LOGISTICHELL_MAINSCENE_H
