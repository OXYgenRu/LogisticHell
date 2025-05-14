//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BUILDINGGRID_H
#define LOGISTICHELL_BUILDINGGRID_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "BuildingBlock.h"
#include "BlockFactory.h"


class Dock;


class BuildingGrid : public ContainerNode {
public:
    static std::shared_ptr<BuildingGrid>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock, sf::Vector2f position,
           float sf_cell_size,
           float b2_cell_size, sf::Vector2i grid_size, std::shared_ptr<BlockFactory> block_factory,
           int render_priority = 0,
           int render_priority_layers = 10
    );


    explicit BuildingGrid(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void
    setup(std::shared_ptr<BuildingGrid> node, std::shared_ptr<Dock> dock, sf::Vector2f position,
          float sf_cell_size,
          float b2_cell_size, sf::Vector2i grid_size, std::shared_ptr<BlockFactory> block_factory
    );

    void clear(EngineContext &ctx);

    void clear_preview(EngineContext &ctx);

    void clear_mask(EngineContext &ctx);

    void set_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx);

    void set_preview_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx);

    void set_mask_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx);

    std::weak_ptr<Dock> dock;
    std::shared_ptr<ContainerNode> cells_layer;
    std::shared_ptr<ContainerNode> preview_cells_layer;
    std::shared_ptr<ContainerNode> mask_cells_layer;
    std::vector<std::vector<std::shared_ptr<BuildingBlock>>> cells;
    std::vector<std::vector<std::shared_ptr<BuildingBlock>>> preview_cells;
    std::vector<std::vector<std::shared_ptr<BuildingBlock>>> mask_cells;
    std::shared_ptr<BlockFactory> block_factory;

    sf::Vector2f position;
    sf::Vector2i grid_size;
    float sf_cell_size;
    float b2_cell_size;
};


#endif //LOGISTICHELL_BUILDINGGRID_H
