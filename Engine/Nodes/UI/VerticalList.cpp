//
// Created by EgorRychkov on 21.05.2025.
//

#include "VerticalList.h"

std::shared_ptr<UI::ListItem>
UI::ListItem::create(const std::shared_ptr<VerticalList> &parent, EngineContext &ctx, const sf::Vector2f &item_size,
                     const std::string &node_id,
                     int render_priority) {
    auto node = std::make_shared<UI::ListItem>(parent, node_id, render_priority);
    UI::ListItem::setup(node, ctx, item_size);
    parent->add_node(node);
    return node;
}

void UI::ListItem::setup(std::shared_ptr<UI::ListItem> &node, EngineContext &ctx, const sf::Vector2f &item_size) {
    node->button = UI::Button::create(node, ctx, "ListItemButton");
    node->button->set_rectangle({0, 0}, item_size);
    node->button->set_color(sf::Color(63, 72, 204));
    node->button->set_hold_reaction(true);
    node->text_layer = Node::create(node, "ListItemTextLayer", 1);
    node->text = Text::create(node->text_layer, "ListItemText");
    node->text->set_font("C:/Windows/Fonts/arial.ttf");
    node->text->set_text("Test text");
}


std::shared_ptr<UI::VerticalList> UI::VerticalList::create(const std::shared_ptr<Node> &parent, EngineContext &ctx,
                                                           const sf::Vector2f &container_size, int list_size,
                                                           const std::string &node_id,
                                                           int render_priority) {
    auto node = std::make_shared<UI::VerticalList>(parent, node_id, render_priority);
    UI::VerticalList::setup(node, ctx, container_size, list_size);
    parent->add_node(node);
    return node;
}

void
UI::VerticalList::setup(std::shared_ptr<UI::VerticalList> &node, EngineContext &ctx, const sf::Vector2f &container_size,
                        int list_size) {
    sf::Vector2f item_size = {container_size.x, container_size.y / float(list_size)};
    node->items.resize(list_size);
    for (int i = 0; i < list_size; i++) {
        node->items[i] = UI::ListItem::create(node, ctx, item_size, "ListItem : " + std::to_string(i));
        node->items[i]->set_position({0, item_size.y * float(i)});
    }
}


int UI::VerticalList::get_list_size() const {
    return int(items.size());
}

std::shared_ptr<UI::ListItem> &UI::VerticalList::get_item(int index) {
    return this->items[index];
}