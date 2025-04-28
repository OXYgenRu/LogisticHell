//
// Created by EgorRychkov on 27.04.2025.
//

#ifndef LOGISTICHELL_MAINSCENE_H
#define LOGISTICHELL_MAINSCENE_H


#include "../../Engine/Scene.h"
#include "Structure/Structure.h"
#include "../../Engine/Nodes/Base/CameraNode.h"
#include "../../Engine/Nodes/Physics/World.h"
#include "../Tests/PhysicsNodes/TestController.h"

class MainScene : public Scene {
public:
    static std::shared_ptr<MainScene> create(int render_priority_layers) {
        auto node = std::make_shared<MainScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    MainScene() : Scene() {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<Structure> structure;
    std::shared_ptr<Structure> static_structure;
    std::shared_ptr<CameraNode> camera;
    std::shared_ptr<World> world;
    std::shared_ptr<TestController> test_controller;

};


#endif //LOGISTICHELL_MAINSCENE_H
