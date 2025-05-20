//
// Created by EgorRychkov on 18.05.2025.
//

#include "Rectangle.h"
#include "../Base/ContainerNode.h"
#include "../../Application.h"

std::shared_ptr<UI::Rectangle>
UI::Rectangle::create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_position, sf::Vector2f space_size,
                      AnchorType anchor_type,
                      AnchorBinding anchor_binding,
                      int render_priority) {
    auto node = std::make_shared<UI::Rectangle>(parent, render_priority);
    parent->add_node(node);
    UI::Rectangle::setup(node, space_position, space_size, anchor_type, anchor_binding);
    return node;
}

void UI::Rectangle::setup(std::shared_ptr<Rectangle> &node, sf::Vector2f &space_position, sf::Vector2f &space_size,
                          AnchorType anchor_type, AnchorBinding anchor_binding) {
    node->anchor.set_space(space_position, space_size);
    node->anchor.set_anchor_type(anchor_type);
    node->anchor.set_anchor_binding(anchor_binding);
}

void UI::Rectangle::set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right) {
    this->top_left = new_top_left;
    this->bottom_right = new_bottom_right;
    this->polygon.setPosition(anchor.get_position(new_top_left));
    this->polygon.setSize(sf::Vector2f(anchor.get_position(new_bottom_right) - anchor.get_position(new_top_left)));
}

void UI::Rectangle::set_texture(const std::string &new_texture_name, EngineContext &ctx) {
    this->polygon.setTexture(ctx.app->texture_atlas->get_texture());
    AtlasRegion region = ctx.app->texture_atlas->get_region(new_texture_name);
    this->polygon.setTextureRect(region.get_int_rect());
}

void UI::Rectangle::set_color(sf::Color color) {
    this->polygon.setFillColor(color);
}


void UI::Rectangle::render(EngineContext &ctx) {
    ctx.app->window->draw(this->polygon);
}