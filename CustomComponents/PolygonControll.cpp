//
// Created by EgorRychkov on 17.04.2025.
//

#include "PolygonControll.h"
#include "MainScene.h"

std::shared_ptr<PolygonControll> PolygonControll::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<PolygonControll>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void PolygonControll::on_key_press(sf::Event &event) {
    if (event.key.code == sf::Keyboard::D) {
        if (auto to = std::static_pointer_cast<MainScene>(this->parent.lock())) {
            for (int i = 0; i < 4; i++) {
                to->polygon_1->polygon.setPoint(i, to->polygon_1->polygon.getPoint(i) + sf::Vector2f(30, 0));
            }

        }
    }
}