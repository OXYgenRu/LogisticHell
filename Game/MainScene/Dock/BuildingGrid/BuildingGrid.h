//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BUILDINGGRID_H
#define LOGISTICHELL_BUILDINGGRID_H


#include "../../../../Engine/Nodes/Base/Node.h"
#include "../../../../Engine/Nodes/UI/Collider.h"
#include "BuildingBlock.h"
#include "BlockFactory.h"


class Dock;


class Cell : public Node {
public:
    static std::shared_ptr<Cell>
    create(const std::shared_ptr<Node> &parent, float sf_cell_size,
           const sf::Vector2i &position,
           const std::shared_ptr<BlockFactory> &block_factory,
           int render_priority = 0
    );


    explicit Cell(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(const std::shared_ptr<Cell> &node, float sf_cell_size,
          const sf::Vector2i &position,
          const std::shared_ptr<BlockFactory> &block_factory
    );

    void set_default_state(EngineContext &ctx);

    void set_background_block(const std::string &new_background_block_id, EngineContext &ctx, int rotation);

    void set_block(const std::string &new_block_id, EngineContext &ctx, int rotation);

    void
    set_preview_background_block(const std::string &new_preview_background_block_id, EngineContext &ctx, int rotation);

    void set_preview_block(const std::string &new_preview_block_id, EngineContext &ctx, int rotation);

    void set_mask_block(const std::string &new_mask_block_id, EngineContext &ctx, int rotation);

    void set_cell_position(const sf::Vector2i &new_cell_position);

private:
    std::shared_ptr<BlockFactory> block_factory;

    std::shared_ptr<BuildingBlock> background_block;
    std::shared_ptr<BuildingBlock> block;
    std::shared_ptr<BuildingBlock> preview_background_block;
    std::shared_ptr<BuildingBlock> preview_block;
    std::shared_ptr<BuildingBlock> mask_block;

    std::string background_block_id;
    std::string block_id;
    std::string preview_background_block_id;
    std::string preview_block_id;
    std::string mask_block_id;
    sf::Vector2i position;
    float sf_cell_size;
};

class BuildingGrid : public Node {
public:
    static std::shared_ptr<BuildingGrid>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Dock> &dock, float sf_cell_size,
           const sf::Vector2i &grid_size, const std::shared_ptr<BlockFactory> &block_factory,
           int render_priority = 0
    );


    explicit BuildingGrid(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(const std::shared_ptr<BuildingGrid> &node, const std::shared_ptr<Dock> &dock, float sf_cell_size,
          const sf::Vector2i &grid_size, const std::shared_ptr<BlockFactory> &block_factory
    );

    void set_default_state(EngineContext &ctx);

    void clear_background(EngineContext &ctx);

    void clear(EngineContext &ctx);

    void clear_preview(EngineContext &ctx);

    void clear_background_preview(EngineContext &ctx);

    void clear_mask(EngineContext &ctx);

    void
    set_background_block(const sf::Vector2i &position, const std::string &block_id, int rotation, EngineContext &ctx);

    void set_block(const sf::Vector2i &position, const std::string &block_id, int rotation, EngineContext &ctx);

    void set_background_preview_block(const sf::Vector2i &position, const std::string &block_id, int rotation,
                                      EngineContext &ctx);

    void set_preview_block(const sf::Vector2i &position, const std::string &block_id, int rotation, EngineContext &ctx);

    void set_mask_block(const sf::Vector2i &position, const std::string &block_id, int rotation, EngineContext &ctx);

    std::weak_ptr<Dock> dock;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    std::shared_ptr<BlockFactory> block_factory;
    std::shared_ptr<UI::Collider> grid_collider;

    sf::Vector2i grid_size;
    float sf_cell_size;
};


#endif //LOGISTICHELL_BUILDINGGRID_H
