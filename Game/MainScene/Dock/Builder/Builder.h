//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BUILDER_H
#define LOGISTICHELL_BUILDER_H

#include "../../Blueprints/Blueprint/Blueprint.h"
#include "memory"
#include "../BuildingGrid/BuildingGrid.h"
#include "../../Blueprints/BlueprintLoader.h"
#include "set"

class Builder {
public:

    static std::shared_ptr<Builder>
    create(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader);

    explicit Builder(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader);

    void set_default_blueprint(EngineContext &ctx);

    void attach_unit(sf::Vector2i position, EngineContext &ctx);

    void destroy_unit(sf::Vector2i position, EngineContext &ctx);

    bool validate_unit_attachment(sf::Vector2i position);

    void set_new_preview_position(sf::Vector2i position, EngineContext &ctx);

    void rotate_preview(EngineContext &ctx);

    int get_preview_rotation();

    sf::Vector2i &get_preview_position();

    void clear_preview(EngineContext &ctx);

    void select_next_preview_component(EngineContext &ctx);

    void select_next_blueprint_component(EngineContext &ctx);

    void find_blueprint_attachment_components();

    void draw_building_preview(EngineContext &ctx);

    void draw_destroying_preview(EngineContext &ctx);

    std::string unit_id;
    std::shared_ptr<Blueprint> blueprint;
    std::shared_ptr<BuildingGrid> building_grid;
    std::weak_ptr<BlueprintLoader> blueprint_loader;
    int unit_index;
private:
    std::vector<std::shared_ptr<BlueprintComponent>> blueprint_attachment_components;
    int preview_rotation = 0;
    sf::Vector2i preview_position;
    int selected_preview_component_index = 0;
    int selected_blueprint_component_index = 0;

};


#endif //LOGISTICHELL_BUILDER_H
