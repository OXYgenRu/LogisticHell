//
// Created by EgorRychkov on 17.04.2025.
//
#include "iostream"
#include "MainScene.h"
#include "PolygonControll.h"
#include "../Engine/Nodes/Base/CameraNode.h"
#include "HexTest.h"

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();


    camera_node = CameraNode::create(scene, ctx, 0, 10);
//    camera_node->set_render_flag(false);
    hex = HexTest::create(camera_node);

    polygon_controller = PolygonControll::create(camera_node);
//    ui_test_node = Polygon::create(camera_node, 1);
//    std::vector<sf::Vector2<float>> c = {{0,    0},
//                                         {1000, 0},
//                                         {1000, 200},
//                                         {0,    200}};
//    ui_test_node->set_polygon(c);
//    ui_test_node->polygon.setFillColor(sf::Color::Green);
//    std::cout << camera_node->get_container_volume() << '\n';


}

void MainScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';
}