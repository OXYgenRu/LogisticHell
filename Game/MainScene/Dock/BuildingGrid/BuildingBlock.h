//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BUILDINGBLOCK_H
#define LOGISTICHELL_BUILDINGBLOCK_H


#include "../../../../Engine/Nodes/Base/Node.h"
#include "../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class BuildingBlock : public Node {
public:
    static std::shared_ptr<BuildingBlock>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, sf::Vector2i cell_position, float sf_cell_size,
           int rotation,  const std::string &texture,
           int render_priority = 0);


    explicit BuildingBlock(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void
    setup(std::shared_ptr<BuildingBlock> node, EngineContext &ctx, sf::Vector2i cell_position, float sf_cell_size,
          int rotation,
          const std::string &texture);


    std::vector<sf::Vector2f> vertices;
    std::shared_ptr<TexturedQuad> textured_quad;
};


#endif //LOGISTICHELL_BUILDINGBLOCK_H
