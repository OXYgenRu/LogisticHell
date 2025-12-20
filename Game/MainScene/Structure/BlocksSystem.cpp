//
// Created by EgorRychkov on 29.07.2025.
//

#include "BlocksSystem.h"
#include "box2d/box2d.h"
#include "../World/GameWorld.h"


std::shared_ptr<BlocksSystem>
BlocksSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                     float block_side_size, const std::string &node_id,
                     int render_priority) {
    auto node = std::make_shared<BlocksSystem>(parent, node_id, render_priority);
    BlocksSystem::setup(node, world, block_side_size);
    parent->add_node(node);
    return node;
}

void BlocksSystem::setup(const std::shared_ptr<BlocksSystem> &node, const std::shared_ptr<GameWorld> &world,
                         float block_side_size) {
    node->world = world;
    node->block_side_size = block_side_size;
}

std::shared_ptr<ComponentBlock> BlocksSystem::create_block(const sf::Vector2i &position, BlueprintBlock &block,
                                                           const std::shared_ptr<Component> &component) {
    float pixel_per_meter = world.lock()->get_pixel_per_meter();

    std::shared_ptr<ComponentBlock> new_block = ComponentBlock::create(component, position, component, max_block_id,
                                                                       "ComponentBlock");
    blocks[max_block_id++] = new_block;
    component->blocks[position.y][position.x] = new_block;
    new_block->set_position(
            {float(position.x) * block_side_size * pixel_per_meter,
             -float(position.y) * block_side_size * pixel_per_meter});


    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = block.density;
    shape_def.material.friction = block.friction;

    b2Polygon polygon;
    b2Vec2 vertices[4];
    vertices[0] = {float(position.x) * block_side_size - block_side_size / 2,
                   float(position.y) * block_side_size + block_side_size / 2};
    vertices[1] = {float(position.x) * block_side_size - block_side_size / 2,
                   float(position.y) * block_side_size - block_side_size / 2};
    vertices[2] = {float(position.x) * block_side_size + block_side_size / 2,
                   float(position.y) * block_side_size - block_side_size / 2};
    vertices[3] = {float(position.x) * block_side_size + block_side_size / 2,
                   float(position.y) * block_side_size + block_side_size / 2};
    b2Hull hull = b2ComputeHull(vertices, 4);
    polygon = b2MakePolygon(&hull, 0);

    new_block->collision_polygon = CollisionPolygon::create(new_block, component->rigid_body,
                                                            shape_def,
                                                            polygon, "BlockCollisionPolygon");
    new_block->collider = UI::Collider::create(new_block, "BlockCollider");

    std::vector<sf::Vector2f> collider_vertices({{-block_side_size / 2, -block_side_size / 2},
                                                 {block_side_size / 2,  -block_side_size / 2},
                                                 {block_side_size / 2,  block_side_size / 2},
                                                 {-block_side_size / 2, block_side_size / 2}});
    for (int i = 0; i < 4; i++) {
        collider_vertices[i] *= pixel_per_meter;
    }
    new_block->collider->set_vertices(collider_vertices);
    return new_block;
}

std::shared_ptr<ComponentBlock> BlocksSystem::get_block(const unsigned int &block_id) {
    auto it = this->blocks.find(block_id);
    if (it == this->blocks.end()) {
        throw std::runtime_error("Block not found");
    }
    return it->second;
}


void BlocksSystem::destroy_block(const std::shared_ptr<ComponentBlock> &block) {
    delete_block(block);
    auto unit = block->get_weak_unit().lock();
    auto component = block->get_weak_component().lock();
    for (auto &to: block->get_render_quads()) {
        unit->delete_render_feature(to->get_feature_name());
    }
    unit->delete_block(block->get_in_component_position());
    component->delete_node(block);
    component->delete_block(block->get_in_component_position());
}


void BlocksSystem::delete_block(const std::shared_ptr<ComponentBlock> &block) {
    auto it = this->blocks.find(block->get_block_id());
    if (it == this->blocks.end()) {
        throw std::runtime_error("Deleting block not found");
    }
    this->blocks.erase(it);
}