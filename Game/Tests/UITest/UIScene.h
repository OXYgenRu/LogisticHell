//
// Created by EgorRychkov on 22.04.2025.
//

#ifndef LOGISTICHELL_UISCENE_H
#define LOGISTICHELL_UISCENE_H

#include "../../../Engine/Scene.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/UI/UICollider.h"

class UIScene : public Scene {
public:
    static std::shared_ptr<UIScene> create(int render_priority_layers) {
        auto node = std::make_shared<UIScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    UIScene() : Scene() {}

    void init_tree(EngineContext &ctx);

    void update(EngineContext &ctx) override;

    std::shared_ptr<CameraNode> camera;
    std::shared_ptr<Polygon> polygon;
    std::shared_ptr<UICollider> ui_collider;

};


#endif //LOGISTICHELL_UISCENE_H
