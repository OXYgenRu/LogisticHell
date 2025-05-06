//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BUILDER_H
#define LOGISTICHELL_BUILDER_H

#include "../../Blueprints/Blueprint/Blueprint.h"
#include "memory"
#include "../BuildingGrid/BuildingGrid.h"

class Builder {
public:

    static std::shared_ptr<Builder> create(std::shared_ptr<BuildingGrid> building_grid);

    explicit Builder(std::shared_ptr<BuildingGrid> building_grid);

    void set_default_blueprint(EngineContext &ctx);

    void attach_block(sf::Vector2i position, EngineContext &ctx);

    bool validate_block_attachment(sf::Vector2i position);

    std::shared_ptr<BlueprintComponent> get_block_attachment_component(sf::Vector2i position);

    void set_attach_direction(int new_attach_direction_index);

    int attach_direction_index = 0;
    std::vector<sf::Vector2i> attach_directions;
    sf::Vector2i attach_direction;
    std::shared_ptr<Blueprint> blueprint;
    std::shared_ptr<BuildingGrid> building_grid;
};


#endif //LOGISTICHELL_BUILDER_H
