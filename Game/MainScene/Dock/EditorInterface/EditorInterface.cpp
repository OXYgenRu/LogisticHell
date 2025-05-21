//
// Created by EgorRychkov on 01.05.2025.
//

#include "EditorInterface.h"
#include "../Dock.h"
#include "../../../../Engine/Application.h"

std::shared_ptr<EditorInterface>
EditorInterface::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<Dock> dock,
                        int render_priority,
                        int render_priority_layers) {
    auto node = std::make_shared<EditorInterface>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    EditorInterface::setup(node, ctx, dock);
    parent->add_node(node);
    return node;
}

void EditorInterface::setup(std::shared_ptr<EditorInterface> node, EngineContext &ctx, std::shared_ptr<Dock> dock) {
    node->dock = dock;

    node->background = UI::Button::create(node, ctx,
                                          ctx.app->get_window_size(),
                                          AnchorType::Absolute, AnchorBinding::CenterDown);
    node->background->set_rectangle({-ctx.app->get_window_size().x / 2, -180}, {ctx.app->get_window_size().x / 2, 0});
    node->background->set_color(sf::Color(63, 72, 204));

    node->text = Text::create(node);
    node->text->set_font("C:/Windows/Fonts/arial.ttf");
    node->text->text.setString("Dock");
    node->text->text.setPosition(1430, 200);
    node->text->text.setFillColor(sf::Color::Black);
    node->text->text.setCharacterSize(30);

    node->selected_unit = Text::create(node);
    node->selected_unit->set_font("C:/Windows/Fonts/arial.ttf");
    node->selected_unit->text.setString("");
    node->selected_unit->text.setPosition(1430, 500);
    node->selected_unit->text.setFillColor(sf::Color::Black);
    node->selected_unit->text.setCharacterSize(30);

    {
        node->attachment_mode = UI::Button::create(node, ctx,  {float(ctx.app->window->getSize().x),
                                                                       float(ctx.app->window->getSize().y)},
                                                   AnchorType::Absolute, AnchorBinding::CenterDown);
        node->attachment_mode->set_rectangle({-ctx.app->get_window_size().x / 2 + 30, -170},
                                             {-ctx.app->get_window_size().x / 2 + 30 + 150, -170 + 150});
        node->attachment_mode->set_texture("attach_icon", ctx);
    }
    {
        node->destroying_mode = UI::Button::create(node, ctx,  {float(ctx.app->window->getSize().x),
                                                                       float(ctx.app->window->getSize().y)},
                                                   AnchorType::Absolute, AnchorBinding::CenterDown);
        node->destroying_mode->set_rectangle({-ctx.app->get_window_size().x / 2 + 330, -170},
                                             {-ctx.app->get_window_size().x / 2 + 330 + 150, -170 + 150});
        node->destroying_mode->set_texture("remove_icon", ctx);
    }
    {
        node->attachment_mode->bind_on_mouse_press([dock, node](sf::Event &event, EngineContext &ctx) {
            node->attachment_mode->set_color(sf::Color(150, 150, 150));

        });
        node->attachment_mode->bind_on_mouse_release([dock, node](sf::Event &event, EngineContext &ctx) {
            dock->editor_controller->set_mode(EditorMode::Attachment, ctx);
            node->attachment_mode->set_color(sf::Color(255, 255, 255));

        });
        node->destroying_mode->bind_on_mouse_release([dock, node](sf::Event &event, EngineContext &ctx) {
            dock->editor_controller->set_mode(EditorMode::Destroying, ctx);
            node->destroying_mode->set_color(sf::Color(255, 255, 255));
        });
        node->destroying_mode->bind_on_mouse_press([dock, node](sf::Event &event, EngineContext &ctx) {
            node->destroying_mode->set_color(sf::Color(150, 150, 150));

        });
    }
}

void EditorInterface::update(EngineContext &ctx) {
    auto dock_ptr = this->dock.lock();
    this->selected_unit->text.setString(dock_ptr->editor_controller->builder->unit_id);
}