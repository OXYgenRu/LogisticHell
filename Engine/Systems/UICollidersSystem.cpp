//
// Created by EgorRychkov on 21.04.2025.
//

#include "UICollidersSystem.h"

#include "../EngineContext.h"
#include "../Application.h"
#include "../Nodes/UI/Collider.h"
#include "../Tools.h"
#include "../Application.h"
#include "../EngineContext.h"
#include "../Systems/Tree.h"

void UICollidersSystem::update(EngineContext &ctx) {
    bool was_used = false;
    for (int i = ctx.app->tree->get_free_tree_index() - 1; i >= 0; i--) {
        if (!ctx.app->tree->get_flatten_tree()[i].is_update_active) {
            continue;
        }
        if (ctx.app->tree->get_flatten_tree()[i].node->get_node_type() == 9) {
            auto node = std::static_pointer_cast<UI::Collider>(ctx.app->tree->get_flatten_tree()[i].node);
            if (was_used) {
                continue;
            }
            for (sf::Event &event: this->control_events) {
                sf::Vector2f pixelPos = ctx.app->window->mapPixelToCoords(sf::Mouse::getPosition(*ctx.app->window));
                sf::Vector2f localPos = ctx.app->tree->get_flatten_tree()[i].transform.getInverse().transformPoint(
                        pixelPos);
                if (!is_point_in_polygon(localPos, node->get_vertices())) {
                    continue;
                }
                if (node != this->last_used_collider) {
                    if (this->last_used_collider != nullptr) {
                        this->last_used_collider->handle_mouse_exit(ctx, localPos);
                    }
                    node->handle_mouse_enter(ctx, localPos);
                }
                this->last_used_collider = node;
                if (event.type == sf::Event::MouseButtonReleased) {
                    node->handle_mouse_release(event, ctx, localPos);
                    was_used = true;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    node->handle_mouse_press(event, ctx, localPos);
                    was_used = true;
                }
                if (event.type == sf::Event::MouseMoved) {
                    node->handle_mouse_move(event, ctx, localPos);
                    was_used = true;
                }
            }
        }
    }
    while (!this->control_events.empty()) {
        this->control_events.pop_back();
    }
}


void UICollidersSystem::collect_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        this->control_events.push_back(event);
    }
    if (event.type == sf::Event::MouseMoved) {
        this->control_events.push_back(event);
    }
//    if (event.type == sf::Event::MouseWheelScrolled) {
//        this->control_events.push_back(event);
//    }
}