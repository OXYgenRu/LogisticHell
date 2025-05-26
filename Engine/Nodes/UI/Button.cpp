//
// Created by EgorRychkov on 18.05.2025.
//

#include "Button.h"
#include "../../Application.h"

std::shared_ptr<UI::Button>
UI::Button::create(const std::shared_ptr<Node> &parent, EngineContext &ctx,
                   int render_priority) {
    auto node = std::make_shared<UI::Button>(parent, render_priority);
    UI::Button::setup(node, ctx);
    parent->add_node(node);
    return node;
}

void UI::Button::setup(std::shared_ptr<Button> &node, EngineContext &ctx) {
    node->is_pressed = false;
    node->color = sf::Color(255, 255, 255);
    node->react_to_hold = false;
    node->rectangle = UI::Rectangle::create(node);
    node->collider = UI::Collider::create(node);
    node->collider->bind_on_mouse_release(
            [node](sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
                node->handle_on_mouse_release(event, ctx);
            });
    node->collider->bind_on_mouse_press(
            [node](sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
                node->handle_on_mouse_press(event, ctx);
            });
    node->collider->bind_on_mouse_moved(
            [node](sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
                node->handle_on_mouse_move(event, ctx);
            });
    node->collider->bind_on_mouse_enter([node](EngineContext &ctx, const sf::Vector2f &local_position) {
        node->handle_on_mouse_enter(ctx);
    });
    node->collider->bind_on_mouse_exit([node](EngineContext &ctx, const sf::Vector2f &local_position) {
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

void UI::Button::set_color(const sf::Color &color) {
    this->color = color;
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
    this->is_pressed = true;
    this->on_mouse_press(event, ctx);
    if (this->react_to_hold) {
        this->rectangle->set_color(sf::Color(static_cast<sf::Uint8>(float(color.r) * 0.8f),
                                             static_cast<sf::Uint8>(float(color.g) * 0.8f),
                                             static_cast<sf::Uint8>(float(color.b) * 0.8f)));
    }
}

void UI::Button::handle_on_mouse_release(sf::Event &event, EngineContext &ctx) {
    if (!this->is_pressed) {
        return;
    }
    if (this->react_to_hold) {
        this->rectangle->set_color(this->color);
    }
    this->is_pressed = false;
    this->on_mouse_release(event, ctx);
}

void UI::Button::handle_on_mouse_move(sf::Event &event, EngineContext &ctx) {
    this->on_mouse_moved(event, ctx);
}

void UI::Button::handle_on_mouse_enter(EngineContext &ctx) {
    this->on_mouse_enter(ctx);
}

void UI::Button::handle_on_mouse_exit(EngineContext &ctx) {
    if (this->react_to_hold and this->is_pressed) {
        this->rectangle->set_color(this->color);
    }
    this->is_pressed = false;
    this->on_mouse_exit(ctx);
}

void UI::Button::set_hold_reaction(bool is_react_to_hold) {
    this->react_to_hold = is_react_to_hold;
}