//
// Created by EgorRychkov on 17.04.2025.
//

#include "PolygonControll.h"
#include "MainScene.h"
#include "iostream"
#include "../Engine/Application.h"

std::shared_ptr<PolygonControll> PolygonControll::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<PolygonControll>(parent, render_priority);
    parent->add_node(node);
    return node;
}


void PolygonControll::update(EngineContext &ctx) {
    auto to = ctx.app->get_current_scene();
    auto scene = std::static_pointer_cast<MainScene>(to);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        std::cout << "d" << '\n';
        for (int i = 0; i < 4; i++) {
            scene->polygon_1->polygon.setPoint(i, scene->polygon_1->polygon.getPoint(i) +
                                                  sf::Vector2f(300 * ctx.last_frame_delta_time, 0));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//        std::cout << "w" << '\n';
        for (int i = 0; i < 4; i++) {
            scene->polygon_1->polygon.setPoint(i, scene->polygon_1->polygon.getPoint(i) +
                                                  sf::Vector2f(0, -300 * ctx.last_frame_delta_time));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        std::cout << "a" << '\n';
        for (int i = 0; i < 4; i++) {
            scene->polygon_1->polygon.setPoint(i, scene->polygon_1->polygon.getPoint(i) +
                                                  sf::Vector2f(-300 * ctx.last_frame_delta_time, 0));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//        std::cout << "s" << '\n';
        for (int i = 0; i < 4; i++) {
            scene->polygon_1->polygon.setPoint(i, scene->polygon_1->polygon.getPoint(i) +
                                                  sf::Vector2f(0, 300 * ctx.last_frame_delta_time));
        }
    }
}