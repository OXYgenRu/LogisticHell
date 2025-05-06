//
// Created by EgorRychkov on 27.04.2025.
//

#ifndef LOGISTICHELL_TEXTUREDQUAD_H
#define LOGISTICHELL_TEXTUREDQUAD_H


#include "../../Base/ContentNode.h"

class TexturedQuad : public ContentNode {
public:
    static std::shared_ptr<TexturedQuad>
    create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit TexturedQuad(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                        render_priority) {}

    static void setup(std::shared_ptr<TexturedQuad> node);

    void set_texture(const std::string &path);

    void set_quad(std::vector<sf::Vector2f> &vertices);

    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;


    sf::VertexArray quad;
    sf::Texture texture;
};


#endif //LOGISTICHELL_TEXTUREDQUAD_H
