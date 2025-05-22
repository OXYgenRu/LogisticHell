//
// Created by EgorRychkov on 22.05.2025.
//

#include "BlocksInventory.h"
#include "../Dock.h"

std::shared_ptr<BlocksInventory>
BlocksInventory::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<Dock> &dock,
                        const sf::Vector2f &container_size, std::shared_ptr<BlueprintLoader> &blueprint_loader,
                        int render_priority,
                        int render_priority_layers) {
    auto node = std::make_shared<BlocksInventory>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    BlocksInventory::setup(node, ctx, dock, container_size, blueprint_loader);
    parent->add_node(node);
    return node;
}

void BlocksInventory::setup(std::shared_ptr<BlocksInventory> &node, EngineContext &ctx, std::shared_ptr<Dock> &dock,
                            const sf::Vector2f &container_size, std::shared_ptr<BlueprintLoader> &blueprint_loader) {
    std::vector<std::string> units = blueprint_loader->get_all_blueprints();
    node->vertical_list = UI::VerticalList::create(node, ctx, container_size, int(units.size()));
    node->dock = dock;
    node->blueprint_loader = blueprint_loader;


    for (int i = 0; i < node->vertical_list->get_list_size(); i++) {
        std::shared_ptr<UI::ListItem> item = node->vertical_list->get_item(i);
        item->text->text.setString(units[i]);
        item->button->bind_on_mouse_release([dock, units, i](sf::Event &event, EngineContext &ctx) {
            dock->editor_controller->set_unit(units[i]);
        });
    }
}