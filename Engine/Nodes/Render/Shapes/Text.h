//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_TEXT_H
#define LOGISTICHELL_TEXT_H

#include "SFML/Graphics.hpp"
#include "../../Base/Node.h"

class Text : public Node {
public:
    static std::shared_ptr<Text> create(const std::shared_ptr<Node> &parent, int render_priority = 0);

    explicit Text(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent, render_priority) {}

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    void set_font(const std::string &path);

    sf::Font font;
    sf::Text text;
};


#endif //LOGISTICHELL_TEXT_H
