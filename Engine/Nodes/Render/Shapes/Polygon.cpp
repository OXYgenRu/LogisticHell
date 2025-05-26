//
// Created by EgorRychkov on 15.04.2025.
//

#include "Polygon.h"
#include "../../Base/Node.h"
#include "../../../EngineContext.h"
#include "../../../Application.h"

std::shared_ptr<Polygon> Polygon::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<Polygon>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void Polygon::set_polygon(std::vector<sf::Vector2<float>> &new_polygon) {
    this->polygon.setPointCount(new_polygon.size());
    this->polygon.setFillColor(sf::Color::Green);
    for (int i = 0; i < new_polygon.size(); i++) {
        this->polygon.setPoint(i, new_polygon[i]);
    }
}

void Polygon::set_polygon() {
    this->polygon.setPointCount(4);
    std::vector<sf::Vector2<float>> new_polygon = {{0,    100},
                                                   {1600, 100},
                                                   {1600, 200},
                                                   {0,    200}};
    this->polygon.setFillColor(sf::Color::Green);
    for (int i = 0; i < this->polygon.getPointCount(); i++) {
        this->polygon.setPoint(i, new_polygon[i]);
    }
}

void Polygon::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->window->draw(this->polygon, states);
}

void Polygon::update(EngineContext &ctx) {

}

int Polygon::get_node_type() const {
    return 4;
}