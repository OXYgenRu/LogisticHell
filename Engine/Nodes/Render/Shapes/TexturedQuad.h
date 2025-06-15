//
// Created by EgorRychkov on 27.04.2025.
//

#ifndef LOGISTICHELL_TEXTUREDQUAD_H
#define LOGISTICHELL_TEXTUREDQUAD_H


#include "../../Base/Node.h"

class TexturedQuad : public Node {
public:
    static std::shared_ptr<TexturedQuad>
    create(const std::shared_ptr<Node> &parent, int render_priority = 0);

    explicit TexturedQuad(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent, render_priority) {}

    static void setup(std::shared_ptr<TexturedQuad> node);

    void set_texture(const std::string &new_texture_name, int rotation, EngineContext &ctx);

    void set_quad(const std::vector<sf::Vector2f> &vertices);

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;


    sf::VertexArray quad;
    std::string texture_name;
};


#endif //LOGISTICHELL_TEXTUREDQUAD_H
