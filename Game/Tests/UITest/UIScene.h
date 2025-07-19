//
// Created by EgorRychkov on 22.04.2025.
//

#ifndef LOGISTICHELL_UISCENE_H
#define LOGISTICHELL_UISCENE_H

#include "../../../Engine/Scene.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/UI/Collider.h"
#include "../../../Engine/Nodes/UI/Button.h"

class UIScene : public Scene {
public:
    static std::shared_ptr<UIScene> create(const std::string &node_id) {
        auto node = std::make_shared<UIScene>(node_id);
        return node;
    }

    UIScene(const std::string &node_id) : Scene(node_id) {}

    void init_tree(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    std::shared_ptr<CameraNode> camera;
    std::shared_ptr<UI::Button> ui_collider;

};


#endif //LOGISTICHELL_UISCENE_H
