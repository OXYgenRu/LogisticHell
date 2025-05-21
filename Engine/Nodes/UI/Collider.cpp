//
// Created by EgorRychkov on 20.04.2025.
//

#include "Collider.h"
#include "../Base/ContainerNode.h"
#include "../../Application.h"

std::shared_ptr<UI::Collider>
UI::Collider::create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_size,
                     AnchorType anchor_type, AnchorBinding anchor_binding, int render_priority) {
    auto node = std::make_shared<UI::Collider>(parent, render_priority);
    UI::Collider::setup(node, space_size, anchor_type, anchor_binding);
    parent->add_node(node);
    return node;
}

void UI::Collider::setup(std::shared_ptr<UI::Collider> node,
                         sf::Vector2f space_size,
                         AnchorType anchor_type, AnchorBinding anchor_binding) {
    node->anchor.set_space(space_size);
    node->anchor.set_anchor_type(anchor_type);
    node->anchor.set_anchor_binding(anchor_binding);
}

void UI::Collider::render(EngineContext &ctx, sf::RenderStates &states) {

}

void UI::Collider::update(EngineContext &ctx) {

}

int UI::Collider::get_node_type() const {
    return 9;
}

void UI::Collider::handle_mouse_press(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
    this->on_mouse_press(event, ctx, local_position);
}

void UI::Collider::handle_mouse_release(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
    this->on_mouse_release(event, ctx, local_position);
}

void UI::Collider::handle_mouse_move(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
    this->on_mouse_moved(event, ctx, local_position);
}

void UI::Collider::handle_mouse_enter(EngineContext &ctx, const sf::Vector2f &local_position) {
    this->on_mouse_enter(ctx, local_position);
}

void UI::Collider::handle_mouse_exit(EngineContext &ctx, const sf::Vector2f &local_position) {
    this->on_mouse_exit(ctx, local_position);
}

void UI::Collider::set_vertices(std::vector<sf::Vector2f> new_vertices) {
    this->vertices.resize(new_vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        this->vertices[i] = this->anchor.get_position(new_vertices[i]);
    }
}

std::vector<sf::Vector2f> &UI::Collider::get_vertices() {
    return this->vertices;
}

void UI::Collider::bind_on_mouse_press(const std::function<void(sf::Event &event, EngineContext &ctx,
                                                                const sf::Vector2f &local_position)> &new_function) {
    this->on_mouse_press = new_function;
}

void
UI::Collider::bind_on_mouse_release(const std::function<void(sf::Event &event, EngineContext &ctx,
                                                             const sf::Vector2f &local_position)> &new_function) {
    this->on_mouse_release = new_function;
}

void UI::Collider::bind_on_mouse_moved(const std::function<void(sf::Event &event, EngineContext &ctx,
                                                                const sf::Vector2f &local_position)> &new_function) {
    this->on_mouse_moved = new_function;
}

void UI::Collider::bind_on_mouse_enter(
        const std::function<void(EngineContext &ctx, const sf::Vector2f &local_position)> &new_function) {
    this->on_mouse_enter = new_function;
}

void UI::Collider::bind_on_mouse_exit(
        const std::function<void(EngineContext &ctx, const sf::Vector2f &local_position)> &new_function) {
    this->on_mouse_exit = new_function;
}