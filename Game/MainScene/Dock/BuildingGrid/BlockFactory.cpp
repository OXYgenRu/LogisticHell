//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlockFactory.h"

void
BlockFactory::register_block(const std::string &unit_id, const std::string &block_id, const std::string &texture) {
    std::string factory_block_id = unit_id + "::" + block_id;
    this->creators[factory_block_id] = [texture](std::shared_ptr<ContainerNode> parent, EngineContext &ctx,
                                                 sf::Vector2i cell_position, float sf_cell_size,
                                                 int rotation,
                                                 int render_priority = 0,
                                                 int render_priority_layers = 10) {
        return BuildingBlock::create(parent, ctx, cell_position, sf_cell_size, rotation, texture,
                                     render_priority,
                                     render_priority_layers);
    };
}

std::shared_ptr<BuildingBlock>
BlockFactory::create_block(const std::string &block_id,
                           std::shared_ptr<ContainerNode> parent, EngineContext &ctx, sf::Vector2i cell_position,
                           float sf_cell_size,
                           int rotation,
                           int render_priority,
                           int render_priority_layers) const {
    auto block_it = (creators).find(block_id);
    if (block_it == creators.end()) {
        throw std::runtime_error("Unknown block ID");
    }
    return block_it->second(parent, ctx, cell_position, sf_cell_size, rotation, render_priority,
                            render_priority_layers);
}