//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTCOMPONENT_H
#define LOGISTICHELL_BLUEPRINTCOMPONENT_H

#include "SFML/Graphics.hpp"
#include "memory"

struct BlueprintBlock {
    int block_id;
    sf::Vector2i unit_offset;

    BlueprintBlock() {
        this->block_id = 0;
        this->unit_offset = {0, 0};
    }

    BlueprintBlock(int block_id, sf::Vector2i unit_offset) {
        this->block_id = block_id;
        this->unit_offset = unit_offset;
    }
};

class BlueprintComponent {
public:
    static std::shared_ptr<BlueprintComponent> create(sf::Vector2i grid_size);

    explicit BlueprintComponent(sf::Vector2i grid_size) {
        this->grid.resize(grid_size.y, std::vector<BlueprintBlock>(grid_size.x));
    }

    void set_block(sf::Vector2i position, BlueprintBlock new_block);

    BlueprintBlock& get_block(sf::Vector2i position);

    std::vector<std::vector<BlueprintBlock>> grid;
};


#endif //LOGISTICHELL_BLUEPRINTCOMPONENT_H
