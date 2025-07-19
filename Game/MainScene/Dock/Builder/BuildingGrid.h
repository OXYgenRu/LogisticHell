//
// Created by EgorRychkov on 12.06.2025.
//

#ifndef LOGISTICHELL_BUILDINGGRID_H
#define LOGISTICHELL_BUILDINGGRID_H


#include "../../../../Engine/Nodes/Base/Node.h"
#include "../../../../Engine/Nodes/UI/Collider.h"
#include "../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"
#include "../../Blueprints/UnitProperties/UnitRenderFeature.h"

class BuildingGrid : public Node {
public:
    static std::shared_ptr<BuildingGrid>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, float sf_cell_size,
           const sf::Vector2i &grid_size,const std::string &node_id, int render_priority = 0);

    explicit BuildingGrid(const std::shared_ptr<Node> &parent, const std::string &node_id,int render_priority = 0) : Node(parent,node_id,
                                                                                               render_priority) {};

    static void
    setup(const std::shared_ptr<BuildingGrid> &node, float sf_cell_size,
          const sf::Vector2i &grid_size, EngineContext &ctx);

    void
    add_render_feature(const UnitRenderFeature &new_feature, EngineContext &ctx);

    void add_preview_render_feature(const UnitRenderFeature &new_feature, const sf::Vector2i &unit_position,
                                    EngineContext &ctx);

    void set_mask(const std::string &texture_name, const sf::Vector2i &position, EngineContext &ctx);

    void remove_features(const sf::Vector2i &position);

    void remove_preview_features(const sf::Vector2i &position);

    std::vector<std::vector<std::shared_ptr<Node>>> render_features;
    std::vector<std::vector<std::shared_ptr<Node>>> preview_render_features;
    std::vector<std::vector<std::shared_ptr<TexturedQuad>>> mask;
    std::shared_ptr<UI::Collider> grid_collider;
    sf::Vector2i grid_size;
    float sf_cell_size;
};


#endif //LOGISTICHELL_BUILDINGGRID_H
