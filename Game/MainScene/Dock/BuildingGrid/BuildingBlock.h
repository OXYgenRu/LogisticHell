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
    create(std::shared_ptr<ContainerNode> parent, sf::Vector2i cell_position, float sf_cell_size,
           sf::Vector2f grid_position,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit BuildingBlock(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    static void
    setup(std::shared_ptr<BuildingBlock> node, sf::Vector2i cell_position, float sf_cell_size,
          sf::Vector2f grid_position,
          const std::string &texture_path);


    std::vector<sf::Vector2f> vertices;
    std::shared_ptr<TexturedQuad> textured_quad;
};

class EmptyBlock : public BuildingBlock {
public:
    static std::shared_ptr<EmptyBlock>
    create(std::shared_ptr<ContainerNode> parent, sf::Vector2i cell_position, float sf_cell_size,
           sf::Vector2f grid_position,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit EmptyBlock(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : BuildingBlock(parent, render_priority) {}

};

class TestConstructionBlock : public BuildingBlock {
public:
    static std::shared_ptr<TestConstructionBlock>
    create(std::shared_ptr<ContainerNode> parent, sf::Vector2i cell_position, float sf_cell_size,
           sf::Vector2f grid_position,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit TestConstructionBlock(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : BuildingBlock(parent, render_priority) {}

};

#endif //LOGISTICHELL_BUILDINGBLOCK_H
