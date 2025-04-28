//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_PHYSICSTESTSCENE_H
#define LOGISTICHELL_PHYSICSTESTSCENE_H

#include "../../../Engine/Scene.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Physics/RigidBody.h"
#include "TestController.h"
#include "TestBox.h"

class PhysicsTestScene : public Scene {
public:
    static std::shared_ptr<PhysicsTestScene> create(int render_priority_layers) {
        auto node = std::make_shared<PhysicsTestScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    PhysicsTestScene() : Scene() {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<CameraNode> camera;

    std::shared_ptr<World> world;

    std::shared_ptr<RigidBody> body, body2;

    std::shared_ptr<TestBox> box1, box2, box3;

    std::shared_ptr<TestController> controller;
};


#endif //LOGISTICHELL_PHYSICSTESTSCENE_H
