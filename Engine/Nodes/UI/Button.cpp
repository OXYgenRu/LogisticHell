//
// Created by EgorRychkov on 18.05.2025.
//

#include "Button.h"
#include "../../Application.h"

std::shared_ptr<UI::Button>
UI::Button::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, sf::Vector2f space_position,
                   sf::Vector2f space_size,
                   AnchorType anchor_type, AnchorBinding anchor_binding,
                   int render_priority,
                   int render_priority_layers) {
    auto node = std::make_shared<UI::Button>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    UI::Button::setup(node, ctx, space_position, space_size, anchor_type, anchor_binding);
    parent->add_node(node);
    return node;
}

void UI::Button::setup(std::shared_ptr<Button> &node, EngineContext &ctx, sf::Vector2f &space_position,
                       sf::Vector2f &space_size,
                       AnchorType &anchor_type, AnchorBinding &anchor_binding) {
    node->rectangle = UI::Rectangle::create(node, space_position, space_size, anchor_type, anchor_binding);
    node->collider = UI::Collider::create(node, space_position, space_size, anchor_type, anchor_binding);
    node->collider->bind_on_mouse_release([node](sf::Event &event, EngineContext &ctx) {
        node->handle_on_mouse_release(event, ctx);
    });
    node->collider->bind_on_mouse_press([node](sf::Event &event, EngineContext &ctx) {
        node->handle_on_mouse_press(event, ctx);
    });
    node->collider->bind_on_mouse_moved([node](sf::Event &event, EngineContext &ctx) {
        node->handle_on_mouse_move(event, ctx);
    });
    node->collider->bind_on_mouse_enter([node](EngineContext &ctx) {
        node->handle_on_mouse_enter(ctx);
    });
    node->collider->bind_on_mouse_exit([node](EngineContext &ctx) {
        node->handle_on_mouse_exit(ctx);
    });
}


void UI::Button::set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right) {
    this->rectangle->set_rectangle(new_top_left, new_bottom_right);
    this->collider->set_vertices({new_top_left,
                                  {new_bottom_right.x, new_top_left.y},
                                  new_bottom_right,
                                  {new_top_left.x, new_bottom_right.y}});
}

void UI::Button::set_texture(const std::string &new_texture_name, EngineContext &ctx) {
    this->rectangle->set_texture(new_texture_name, ctx);
}

void UI::Button::set_color(sf::Color color) {
    this->rectangle->set_color(color);
}

void UI::Button::bind_on_mouse_press(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function) {
    this->on_mouse_press = new_function;
}

void UI::Button::bind_on_mouse_release(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function) {
    this->on_mouse_release = new_function;
}

void UI::Button::bind_on_mouse_moved(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function) {
    this->on_mouse_moved = new_function;
}

void UI::Button::bind_on_mouse_enter(const std::function<void(EngineContext &ctx)> &new_function) {
    this->on_mouse_enter = new_function;
}

void UI::Button::bind_on_mouse_exit(const std::function<void(EngineContext &ctx)> &new_function) {
    this->on_mouse_exit = new_function;
}

void UI::Button::handle_on_mouse_press(sf::Event &event, EngineContext &ctx) {
    this->on_mouse_press(event, ctx);
}

void UI::Button::handle_on_mouse_release(sf::Event &event, EngineContext &ctx) {
    this->on_mouse_release(event, ctx);
}

void UI::Button::handle_on_mouse_move(sf::Event &event, EngineContext &ctx) {
    this->on_mouse_moved(event, ctx);
}

void UI::Button::handle_on_mouse_enter(EngineContext &ctx) {
    this->on_mouse_enter(ctx);
}

void UI::Button::handle_on_mouse_exit(EngineContext &ctx) {
    this->on_mouse_exit(ctx);
}