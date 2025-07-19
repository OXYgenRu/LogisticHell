//
// Created by EgorRychkov on 22.05.2025.
//

#include <iostream>
#include "BlocksInventory.h"
#include "../Dock.h"

std::shared_ptr<BlocksInventory>
BlocksInventory::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
                        const sf::Vector2f &container_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader,
                        const std::string &node_id,
                        int render_priority) {
    auto node = std::make_shared<BlocksInventory>(parent, node_id, render_priority);
    BlocksInventory::setup(node, ctx, dock, container_size, blueprint_loader);
    parent->add_node(node);
    return node;
}

void BlocksInventory::setup(const std::shared_ptr<BlocksInventory> &node, EngineContext &ctx,
                            const std::shared_ptr<Dock> &dock,
                            const sf::Vector2f &container_size,
                            const std::shared_ptr<BlueprintLoader> &blueprint_loader) {
    std::vector<std::string> units = blueprint_loader->get_all_units();
    std::weak_ptr<Dock> weak_dock = dock;
    node->vertical_list = UI::VerticalList::create(node, ctx, container_size, int(units.size()),
                                                   "UnitsInventoryVerticalList");
    node->dock = dock;
    node->blueprint_loader = blueprint_loader;
    for (int i = 0; i < node->vertical_list->get_list_size(); i++) {
        std::shared_ptr<UI::ListItem> item = node->vertical_list->get_item(i);
        item->text->set_text(units[i]);
        item->text->set_character_size(24);
        item->text->set_font("Minecraftia-Regular.ttf");
        item->text->set_color(sf::Color(255, 255, 255));
        item->button->bind_on_mouse_release([weak_dock, units, i](sf::Event &event, EngineContext &ctx) {
            weak_dock.lock()->editor_controller->set_unit(units[i], ctx);
        });
    }
}