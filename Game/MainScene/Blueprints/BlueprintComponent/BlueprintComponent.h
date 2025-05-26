//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTCOMPONENT_H
#define LOGISTICHELL_BLUEPRINTCOMPONENT_H

#include "SFML/Graphics.hpp"
#include "memory"

struct BlueprintBlock {
    std::string block_id;
    std::string background_block_id;
    sf::Vector2i unit_offset;
    sf::Vector2i unit_size;
    int rotation;
//    bool

    BlueprintBlock() {
        this->block_id = "empty_block::empty_block";
        this->background_block_id = "void_block::void_block";
        this->unit_offset = {0, 0};
        this->rotation = 0;
    }

    BlueprintBlock(std::string block_id, std::string background_block_id, sf::Vector2i unit_offset,
                   sf::Vector2i unit_size, int rotation) {
        this->block_id = block_id;
        this->background_block_id = background_block_id;
        this->unit_offset = unit_offset;
        this->unit_size = unit_size;
        this->rotation = rotation;
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
