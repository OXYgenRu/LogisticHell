//
// Created by EgorRychkov on 01.05.2025.
//

#include "EditorInterface.h"
#include "../Dock.h"
#include "../../../../Engine/Application.h"

std::shared_ptr<EditorInterface>
EditorInterface::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
                        const std::shared_ptr<BlueprintLoader> &blueprint_loader, const std::string &node_id,
                        int render_priority) {
    auto node = std::make_shared<EditorInterface>(parent, node_id, render_priority);
    EditorInterface::setup(node, ctx, dock, blueprint_loader);
    parent->add_node(node);
    return node;
}

void EditorInterface::setup(const std::shared_ptr<EditorInterface> &node, EngineContext &ctx,
                            const std::shared_ptr<Dock> &dock,
                            const std::shared_ptr<BlueprintLoader> &blueprint_loader) {

    std::weak_ptr<Dock> weak_dock = dock;

    node->dock = dock;
    node->buttons_layer = Node::create(node, "EditorInterfaceButtonsLayer");
    node->buttons_layer->set_position({0, ctx.app->get_window_size().y - 130});
    {
        node->buttons_layer_background = UI::Button::create(node->buttons_layer, ctx,
                                                            "EditorInterfaceButtonsLayerBackground", 1);
        node->buttons_layer_background->set_rectangle({0, 0}, {ctx.app->get_window_size().x, 130});
        node->buttons_layer_background->set_color(sf::Color(63, 72, 204));

        node->attachment_mode = UI::Button::create(node->buttons_layer, ctx, "AttachmentModeButton", 2);
        node->attachment_mode->set_rectangle({30, 30},
                                             {120, 120});
        node->attachment_mode->set_texture("attach_icon", ctx);
        node->attachment_mode->set_hold_reaction(true);


        node->assemble_blueprint = UI::Button::create(node->buttons_layer, ctx, "AssembleBlueprintButton", 2);
        node->assemble_blueprint->set_texture("assemble_icon", ctx);
        node->assemble_blueprint->set_hold_reaction(true);
        node->assemble_blueprint->set_rectangle({270, 30}, {360, 120});

        node->destroying_mode = UI::Button::create(node->buttons_layer, ctx, "DestroyingModeButton", 2);
        node->destroying_mode->set_rectangle({150, 30},
                                             {240, 120});
        node->destroying_mode->set_texture("remove_icon", ctx);
        node->destroying_mode->set_hold_reaction(true);

        node->quit_dock = UI::Button::create(node->buttons_layer, ctx, "QuitDockButton", 2);
        node->quit_dock->set_rectangle({390, 30}, {480, 120});
        node->quit_dock->set_texture("quit_dock", ctx);
        node->quit_dock->set_hold_reaction(true);


    }


    {
        node->attachment_mode->bind_on_mouse_release([weak_dock](sf::Event &event, EngineContext &ctx) {
            weak_dock.lock()->editor_controller->set_mode(EditorMode::Attachment, ctx);

        });
        node->destroying_mode->bind_on_mouse_release([weak_dock](sf::Event &event, EngineContext &ctx) {
            weak_dock.lock()->editor_controller->set_mode(EditorMode::Destroying, ctx);
        });
    }
    node->inventory = BlocksInventory::create(node, ctx, dock, {300, 800}, blueprint_loader, "Inventory", 3);
    node->inventory->set_position({ctx.app->get_window_size().x - 300, 0});
}

void EditorInterface::update(EngineContext &ctx) {
//    auto dock_ptr = this->dock.lock();
//    this->selected_unit->text.setString(dock_ptr->editor_controller->builder->unit_id);
}