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

    void set_new_preview_position(sf::Vector2i position, EngineContext &ctx);

    void rotate_preview(EngineContext &ctx);

    int get_preview_rotation();

    sf::Vector2i &get_preview_position();

    void clear_preview(EngineContext &ctx);

    int attach_direction_index = 0;

    std::string unit_id;
    std::vector<sf::Vector2i> attach_directions;
    sf::Vector2i attach_direction;


    std::shared_ptr<Blueprint> blueprint;
    std::shared_ptr<BuildingGrid> building_grid;

    std::weak_ptr<BlueprintLoader> blueprint_loader;
private:
    void update_preview(EngineContext &ctx);

    int preview_rotation = 0;
    sf::Vector2i preview_position;

};


#endif //LOGISTICHELL_BUILDER_H
