//
// Created by EgorRychkov on 16.05.2025.
//

#include "UIPolygon.h"
#include "../../Application.h"

std::shared_ptr<UIPolygon>
UIPolygon::create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_size,
                  AnchorType anchor_type, AnchorBinding anchor_binding,
                  int render_priority) {
    auto node = std::make_shared<UIPolygon>(parent, render_priority);
    UIPolygon::setup(node, space_size, anchor_type, anchor_binding);
    parent->add_node(node);
    return node;
}

void UIPolygon::setup(std::shared_ptr<UIPolygon> &node, sf::Vector2f &space_size,
                      AnchorType anchor_type, AnchorBinding anchor_binding) {
    node->vertices.resize(4);
    node->anchor.set_space(space_size);
    node->anchor.set_anchor_type(anchor_type);
    node->anchor.set_anchor_binding(anchor_binding);
}

void UIPolygon::set_polygon(std::vector<sf::Vector2f> &new_polygon) {
    this->vertices.resize(new_polygon.size());
    this->polygon.setPointCount(new_polygon.size());
    for (int i = 0; i < new_polygon.size(); i++) {
        this->vertices[i] = new_polygon[i];
        this->polygon.setPoint(i, this->anchor.get_position(this->vertices[i]));
    }
}

void UIPolygon::set_color(sf::Color color) {
    this->polygon.setFillColor(color);
}

void UIPolygon::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->window->draw(this->polygon);
}