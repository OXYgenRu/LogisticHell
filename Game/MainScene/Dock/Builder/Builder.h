//
// Created by EgorRychkov on 04.05.2025.
//

#ifndef LOGISTICHELL_BUILDER_H
#define LOGISTICHELL_BUILDER_H

#include "../../Blueprints/Blueprint/Blueprint.h"
#include "memory"
#include "../../Blueprints/BlueprintLoader.h"
#include "set"
#include "../../../../Engine/EngineContext.h"
#include "../../../../Engine/Nodes/Base/Node.h"
#include "BuildingGrid.h"

class GameWorld;

class Builder {
public:

    static std::shared_ptr<Builder>
    create(const std::shared_ptr<BuildingGrid> &building_grid, const std::shared_ptr<GameWorld> &world);

    explicit Builder(const std::shared_ptr<BuildingGrid> &building_grid, const std::shared_ptr<GameWorld> &world);

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

    void set_unit_index(const unsigned int &new_unit_index);

    void set_blueprint(const std::shared_ptr<Blueprint> &new_blueprint, EngineContext &ctx);


    unsigned int unit_index;
    std::shared_ptr<Blueprint> blueprint;
    std::shared_ptr<BuildingGrid> building_grid;
private:
    std::weak_ptr<GameWorld> world;
    std::vector<std::shared_ptr<BlueprintComponent>> blueprint_attachment_components;
    int preview_rotation = 0;
    sf::Vector2i preview_position;
    int selected_preview_component_index = 0;
    int selected_blueprint_component_index = 0;

};


#endif //LOGISTICHELL_BUILDER_H
