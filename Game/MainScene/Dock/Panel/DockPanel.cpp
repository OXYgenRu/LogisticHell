//
// Created by EgorRychkov on 01.05.2025.
//

#include "DockPanel.h"
#include "../Dock.h"

std::shared_ptr<DockPanel> DockPanel::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock,
                                             int render_priority,
                                             int render_priority_layers) {
    auto node = std::make_shared<DockPanel>(parent, render_priority);
    DockPanel::setup(node, dock);
    parent->add_node(node);
    return node;
}

void DockPanel::setup(std::shared_ptr<DockPanel> node, std::shared_ptr<Dock> dock) {
    node->dock = dock;

    std::vector<sf::Vector2f> polygon = {{1400, 0},
                                         {1600, 0},
                                         {1600, 900},
                                         {1400, 900}};

    node->polygon = Polygon::create(node);
    node->polygon->set_polygon(polygon);
    node->polygon->polygon.setFillColor(sf::Color(63, 72, 204));

    node->text = Text::create(node);
    node->text->set_font("C:/Windows/Fonts/arial.ttf");
    node->text->text.setString("Dock");
    node->text->text.setPosition(1430, 200);
    node->text->text.setFillColor(sf::Color::Black);
    node->text->text.setCharacterSize(30);
}

void DockPanel::update(EngineContext &ctx) {
    auto dock_ptr = this->dock.lock();
    this->text->text.setString(std::to_string(dock_ptr->builder->attach_direction_index));
}