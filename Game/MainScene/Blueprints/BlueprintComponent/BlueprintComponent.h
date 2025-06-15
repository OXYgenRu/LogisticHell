//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTCOMPONENT_H
#define LOGISTICHELL_BLUEPRINTCOMPONENT_H

#include "SFML/Graphics.hpp"
#include "memory"


enum class BlockType {
    Empty,
    BusyAttachable,
    BusyLocked
};

struct BlueprintBlock {
    BlockType type;

    BlueprintBlock() {
        type = BlockType::Empty;
    }

    BlueprintBlock(BlockType block_type) {
        type = block_type;
    }
};

class BlueprintComponent {
public:
    static std::shared_ptr<BlueprintComponent> create(sf::Vector2i grid_size);

    explicit BlueprintComponent(sf::Vector2i grid_size) {
        this->grid.resize(grid_size.y, std::vector<BlueprintBlock>(grid_size.x));
    }

    void set_block(sf::Vector2i position, BlueprintBlock new_block);

    void delete_block(sf::Vector2i position);

    sf::Vector2i get_grid_size();

    BlueprintBlock &get_block(sf::Vector2i position);

private:    
    std::vector<std::vector<BlueprintBlock>> grid;
};


#endif //LOGISTICHELL_BLUEPRINTCOMPONENT_H
