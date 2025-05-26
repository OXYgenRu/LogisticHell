//
// Created by EgorRychkov on 10.05.2025.
//

#ifndef LOGISTICHELL_BLOCKFACTORY_H
#define LOGISTICHELL_BLOCKFACTORY_H

#include "memory"
#include "BuildingBlock.h"

class BlockFactory {
public:
    using block_creator = std::function<std::shared_ptr<BuildingBlock>(const std::shared_ptr<Node> &parent,
                                                                       EngineContext &ctx, sf::Vector2i cell_position,
                                                                       float sf_cell_size, int rotation,
                                                                       int render_priority)>;

    void register_block(const std::string &unit_id, const std::string &block_id, const std::string &texture);

    std::shared_ptr<BuildingBlock>
    create_block(const std::string &block_id, const std::shared_ptr<Node> &parent,
                 EngineContext &ctx, sf::Vector2i cell_position, float sf_cell_size,
                 int rotation,
                 int render_priority = 0) const;

private:
    std::unordered_map<std::string, block_creator> creators;
};


#endif //LOGISTICHELL_BLOCKFACTORY_H
