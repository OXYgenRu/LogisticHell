//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_PHYSICSSCENE_H
#define LOGISTICHELL_PHYSICSSCENE_H


#include "../../../Engine/Scene.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "BoxExample.h"

class PhysicsScene : public Scene {
public:
    static std::shared_ptr<PhysicsScene> create(int render_priority_layers) {
        auto node = std::make_shared<PhysicsScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    PhysicsScene() : Scene() {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<CameraNode> camera;

    std::shared_ptr<World> world;
    std::shared_ptr<BoxExample> box;

};


#endif //LOGISTICHELL_PHYSICSSCENE_H
