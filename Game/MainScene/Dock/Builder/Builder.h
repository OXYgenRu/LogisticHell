//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BUILDER_H
#define LOGISTICHELL_BUILDER_H

#include "../../Blueprints/Blueprint/Blueprint.h"
#include "memory"
#include "../BuildingGrid/BuildingGrid.h"
#include "../../Blueprints/BlueprintLoader.h"

class Builder {
public:

    static std::shared_ptr<Builder>
    create(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader);

    explicit Builder(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader);

    void set_default_blueprint(EngineContext &ctx);

    void attach_unit(sf::Vector2i position, EngineContext &ctx);

    bool validate_unit_attachment(sf::Vector2i position);

    void set_attach_direction(int new_attach_direction_index);

    void update_mask(sf::Vector2i position, EngineContext &ctx);

    void clear_mask(EngineContext &ctx);

    int attach_direction_index = 0;
    std::string unit_id;
    std::vector<sf::Vector2i> attach_directions;
    sf::Vector2i attach_direction;
    sf::Vector2i unit_mask_position;

    std::shared_ptr<Blueprint> blueprint;
    std::shared_ptr<BuildingGrid> building_grid;

    std::weak_ptr<BlueprintLoader> blueprint_loader;
};


#endif //LOGISTICHELL_BUILDER_H
