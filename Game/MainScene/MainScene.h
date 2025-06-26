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

class MainScene : public Scene {
public:
    static std::shared_ptr<MainScene> create(int render_priority_layers) {
        auto node = std::make_shared<MainScene>();
        return node;
    }

    MainScene() : Scene() {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<UI::Collider> background_collider;
    std::shared_ptr<CameraNode> world_camera;
    std::shared_ptr<World> world;
    std::shared_ptr<StructuresSystem> structures_system;
    std::shared_ptr<BlueprintLoader> blueprint_loader;
    std::shared_ptr<Dock> dock;

};


#endif //LOGISTICHELL_MAINSCENE_H
