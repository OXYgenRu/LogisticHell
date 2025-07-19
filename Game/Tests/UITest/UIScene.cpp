//
// Created by EgorRychkov on 22.04.2025.
//

#include "UIScene.h"
#include "../../../Engine/Nodes/Base/CameraNode.h"
#include "TestCollider.h"

void UIScene::update(EngineContext &ctx) {

}


void UIScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    camera = CameraNode::create(scene, ctx, "Camera");

    std::vector<sf::Vector2f> a = {{300, 300},
                                   {500, 300},
                                   {500, 500},
                                   {300, 500}};
//    camera->get_transformable().setRotation(20);

//    c1->set_render_flag(false);
    ui_collider = UI::Button::create(camera, ctx, "UiCollider");
    ui_collider->set_rectangle({0, 0}, {100, 100});
//    ui_collider->vertices = a;
}