//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_HEXTEST_H
#define LOGISTICHELL_HEXTEST_H

#include "../Engine/Nodes/Base/ContentNode.h"

class HexTest : public ContentNode {
public:
    static std::shared_ptr<HexTest> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit HexTest(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                   render_priority) {}


    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    sf::RenderTexture renderTexture;
    sf::VertexArray hex;

    sf::Sprite sprite;

};


#endif //LOGISTICHELL_HEXTEST_H
