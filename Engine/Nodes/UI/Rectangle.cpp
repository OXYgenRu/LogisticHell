//
// Created by EgorRychkov on 18.05.2025.
//

#include "Rectangle.h"
#include "../Base/Node.h"
#include "../../Application.h"

std::shared_ptr<UI::Rectangle>
UI::Rectangle::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, int render_priority) {
    auto node = std::make_shared<UI::Rectangle>(parent, render_priority);
    parent->add_node(node);
    UI::Rectangle::setup(node, ctx);
    return node;
}

void UI::Rectangle::setup(std::shared_ptr<Rectangle> &node, EngineContext &ctx) {
    node->vertices.setPrimitiveType(sf::Quads);
    node->vertices.resize(4);
    node->set_texture("white", ctx);
}

void UI::Rectangle::set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right) {
    this->top_left = new_top_left;
    this->bottom_right = new_bottom_right;
    this->set_position(new_top_left);
    this->vertices[1].position = {0, 0};
    this->vertices[2].position = {new_bottom_right.x - new_top_left.x, 0};
    this->vertices[3].position = {new_bottom_right.x - new_top_left.x, new_bottom_right.y - new_top_left.y};
    this->vertices[0].position = {0, new_bottom_right.y - new_top_left.y};
}

void UI::Rectangle::set_texture(const std::string &new_texture_name, EngineContext &ctx) {
    AtlasRegion region = ctx.app->texture_atlas->get_region(new_texture_name);
    for (int i = 0; i < 4; i++) {
        this->vertices[i].texCoords = region.get_rect()[i];
    }

}

void UI::Rectangle::set_color(sf::Color color) {
    for (int i = 0; i < 4; i++) {
        this->vertices[i].color = color;
    }
}


void UI::Rectangle::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->batch->set_texture(*ctx.app->texture_atlas->get_texture(), ctx);
    ctx.app->batch->add_vertices(this->vertices, states.transform);
}