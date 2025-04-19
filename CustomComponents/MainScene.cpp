//
// Created by EgorRychkov on 17.04.2025.
//
#include "iostream"
#include "MainScene.h"
#include "PolygonControll.h"
#include "../Engine/Nodes/Base/CameraNode.h"

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();


    camera_node = CameraNode::create(scene, ctx, 0, 10);
    ui_layer = ContainerNode::create(scene, 1);
    polygon_1 = Polygon::create(camera_node);
    std::vector<sf::Vector2<float>> b = {{150, 100},
                                         {250, 100},
                                         {250, 200},
                                         {150, 200}};
    polygon_1->set_polygon(b);
    polygon_1->polygon.setFillColor(sf::Color::Yellow);
    polygon_controller = PolygonControll::create(camera_node);

    ui_test_node = Polygon::create(ui_layer, 1);
    std::vector<sf::Vector2<float>> c = {{0,    0},
                                         {1000, 0},
                                         {1000, 200},
                                         {0,    200}};
    ui_test_node->set_polygon(c);
    ui_test_node->polygon.setFillColor(sf::Color::Green);
}

void MainScene::update(EngineContext &ctx) {
    std::cout << 1 / ctx.last_frame_delta_time << '\n';
}