//
// Created by EgorRychkov on 17.06.2025.
//

#include "ComponentBlock.h"
#include "Component.h"


std::shared_ptr<ComponentBlock>
ComponentBlock::create(const std::shared_ptr<Node> &parent, const sf::Vector2i &in_component_position,
                       const std::shared_ptr<Component> &component, const unsigned int &block_id,
                       const std::string &node_id,
                       int render_priority) {
    auto node = std::make_shared<ComponentBlock>(parent, node_id, render_priority);
    ComponentBlock::setup(node, in_component_position, component, block_id);
    parent->add_node(node);
    return node;
}

void ComponentBlock::setup(const std::shared_ptr<ComponentBlock> &node, const sf::Vector2i &in_component_position,
                           const std::shared_ptr<Component> &component, const unsigned int &block_id) {
    node->in_component_position = in_component_position;
    node->component = component;
    node->block_id = block_id;
}

ComponentBlock::~ComponentBlock(){
    std::cout << "Block destroyed" << '\n';
}

void ComponentBlock::add_render_quad(const std::shared_ptr<UnitRenderQuad> &new_quad) {
    this->render_quads.push_back(new_quad);
}

void ComponentBlock::delete_render_quads() {
    this->render_quads.clear();
}

std::vector<std::shared_ptr<UnitRenderQuad>> &ComponentBlock::get_render_quads() {
    return this->render_quads;
}

void ComponentBlock::set_unit(const std::shared_ptr<Unit> &new_unit) {
    this->unit = new_unit;
}

const sf::Vector2i &ComponentBlock::get_in_component_position() {
    return this->in_component_position;
}


std::weak_ptr<Unit> ComponentBlock::get_weak_unit() {
    return this->unit;
}

std::weak_ptr<Component> ComponentBlock::get_weak_component() {
    return this->component;
}

const unsigned int &ComponentBlock::get_block_id() {
    return this->block_id;
}