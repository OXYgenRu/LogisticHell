//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BUILDINGBLOCK_H
#define LOGISTICHELL_BUILDINGBLOCK_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class BuildingBlock : public ContainerNode {
public:
    static std::shared_ptr<BuildingBlock>
    create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, sf::Vector2i cell_position, float sf_cell_size,
           int rotation, const std::string &texture_name,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit BuildingBlock(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void
    setup(std::shared_ptr<BuildingBlock> node, EngineContext &ctx, sf::Vector2i cell_position, float sf_cell_size,int rotation,
          const std::string &texture_name);


    std::vector<sf::Vector2f> vertices;
    std::shared_ptr<TexturedQuad> textured_quad;
};


#endif //LOGISTICHELL_BUILDINGBLOCK_H
