//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlockFactory.h"

void
BlockFactory::register_block(const std::string &unit_id, const std::string &block_id, const std::string &texture) {
    std::string factory_block_id = unit_id + "::" + block_id;
    this->creators[factory_block_id] = [texture](const std::shared_ptr<Node> &parent,
                                                                     EngineContext &ctx,
                                                                     sf::Vector2i cell_position, float sf_cell_size,
                                                                     int rotation,
                                                                     int render_priority = 0) {
        return BuildingBlock::create(parent, ctx, cell_position, sf_cell_size, rotation, texture, render_priority);
    };
}

std::shared_ptr<BuildingBlock>
BlockFactory::create_block(const std::string &block_id,
                           const std::shared_ptr<Node> &parent, EngineContext &ctx, sf::Vector2i cell_position,
                           float sf_cell_size,
                           int rotation,
                           int render_priority) const {
    auto block_it = (creators).find(block_id);
    if (block_it == creators.end()) {
        throw std::runtime_error("Unknown block ID");
    }
    return block_it->second(parent, ctx, cell_position, sf_cell_size, rotation, render_priority);
}