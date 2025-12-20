//
// Created by EgorRychkov on 16.06.2025.
//

#ifndef LOGISTICHELL_UNITRENDERQUAD_H
#define LOGISTICHELL_UNITRENDERQUAD_H

#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class UnitRenderQuad : public TexturedQuad {
public:
    static std::shared_ptr<UnitRenderQuad>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::string &feature_name,
           const std::string &texture_name,
           const sf::Vector2i &anchor_block,
           const sf::Vector2f &position, const std::vector<sf::Vector2f> &vertices, float angle,
           float sf_block_side_size, const std::string &node_id,
           int render_priority = 0);


    explicit UnitRenderQuad(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : TexturedQuad(parent, node_id,
                           render_priority) {};

    static void setup(const std::shared_ptr<UnitRenderQuad> &node, EngineContext &ctx, const std::string &feature_name,
                      const std::string &texture_name,
                      const sf::Vector2i &anchor_block,
                      const sf::Vector2f &position, const std::vector<sf::Vector2f> &vertices, float angle,
                      float sf_block_side_size);

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    const std::string &get_feature_name() const;

private:
    std::string feature_name;
    sf::Transform feature_transform;
    sf::Vector2i anchor_block;
};


#endif //LOGISTICHELL_UNITRENDERQUAD_H
