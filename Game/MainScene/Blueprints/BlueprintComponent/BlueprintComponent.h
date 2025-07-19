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

enum class ComponentBodyType {
    Dynamic,
    Static,
    Kinematic,
};

struct BlueprintBlock {
    BlockType type;
    float density;
    float friction;

    BlueprintBlock() {
        type = BlockType::Empty;
        density = 1000;
        friction = 0.3;
    }

    BlueprintBlock(BlockType block_type, float new_density, float new_friction) {
        type = block_type;
        density = new_density;
        friction = new_friction;
    }
};

class BlueprintComponent {
public:
    static std::shared_ptr<BlueprintComponent> create(sf::Vector2i grid_size);

    explicit BlueprintComponent(sf::Vector2i grid_size) {
        this->grid.resize(grid_size.y, std::vector<BlueprintBlock>(grid_size.x));
        this->body_type = ComponentBodyType::Dynamic;
    }

    void set_body_type(ComponentBodyType new_type);

    const ComponentBodyType &get_body_type();

    void set_block(sf::Vector2i position, BlueprintBlock new_block);

    void delete_block(sf::Vector2i position);

    sf::Vector2i get_grid_size();

    BlueprintBlock &get_block(sf::Vector2i position);

private:
    ComponentBodyType body_type;
    std::vector<std::vector<BlueprintBlock>> grid;
};


#endif //LOGISTICHELL_BLUEPRINTCOMPONENT_H
