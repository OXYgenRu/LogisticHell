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
    c1 = Node::create(scene);
    camera = CameraNode::create(c1, ctx);

    std::vector<sf::Vector2f> a = {{300, 300},
                                   {500, 300},
                                   {500, 500},
                                   {300, 500}};
//    camera->get_transformable().setRotation(20);
    polygon = Polygon::create(camera);
    polygon->set_polygon(a);
//    c1->set_render_flag(false);
    ui_collider = TestCollider::create(camera);
//    ui_collider->vertices = a;
}