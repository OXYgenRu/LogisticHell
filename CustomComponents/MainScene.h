//
// Created by EgorRychkov on 17.04.2025.
//

#ifndef LOGISTICHELL_MAINSCENE_H
#define LOGISTICHELL_MAINSCENE_H


#include "../Engine/Scene.h"
#include "../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../Engine/Nodes/Base/ContainerNode.h"
#include "PolygonControll.h"
#include "../Engine/Nodes/Base/CameraNode.h"

class MainScene : public Scene {
public:
    static std::shared_ptr<MainScene> create(int render_priority_layers) {
        auto node = std::make_shared<MainScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    MainScene() : Scene() {}

    void init_tree(EngineContext &ctx);

    void update(EngineContext &ctx) override;

    std::shared_ptr<PolygonControll> polygon_controller;
    std::shared_ptr<Polygon> polygon_1;
    std::shared_ptr<CameraNode> camera_node;
    std::shared_ptr<Polygon> ui_test_node;
    std::shared_ptr<ContainerNode> ui_layer;
};


#endif //LOGISTICHELL_MAINSCENE_H
