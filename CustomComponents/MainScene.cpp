//
// Created by EgorRychkov on 17.04.2025.
//

#include "MainScene.h"
#include "PolygonControll.h"

void MainScene::init_tree() {
    auto scene = shared_from_this();

    polygon_1 = Polygon::create(scene);
    std::vector<sf::Vector2<float>> b = {{150, 100},
                                         {250, 100},
                                         {250, 200},
                                         {150, 200}};
    polygon_1->set_polygon(b);
    polygon_1->polygon.setFillColor(sf::Color::Yellow);
    polygon_controller = PolygonControll::create(scene);

}