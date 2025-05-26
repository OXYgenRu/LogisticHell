//
// Created by EgorRychkov on 18.05.2025.
//

#include "Rectangle.h"
#include "../Base/Node.h"
#include "../../Application.h"

std::shared_ptr<UI::Rectangle>
UI::Rectangle::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<UI::Rectangle>(parent, render_priority);
    parent->add_node(node);
    UI::Rectangle::setup(node);
    return node;
}

void UI::Rectangle::setup(std::shared_ptr<Rectangle> &node) {

}

void UI::Rectangle::set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right) {
    this->top_left = new_top_left;
    this->bottom_right = new_bottom_right;
    this->set_position(new_top_left);
    this->polygon.setSize(new_bottom_right - new_top_left);
}

void UI::Rectangle::set_texture(const std::string &new_texture_name, EngineContext &ctx) {
    this->polygon.setTexture(ctx.app->texture_atlas->get_texture());
    AtlasRegion region = ctx.app->texture_atlas->get_region(new_texture_name);
    this->polygon.setTextureRect(region.get_int_rect());
}

void UI::Rectangle::set_color(sf::Color color) {
    this->polygon.setFillColor(color);
}


void UI::Rectangle::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->window->draw(this->polygon, states);
}