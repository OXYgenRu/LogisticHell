//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_TEXT_H
#define LOGISTICHELL_TEXT_H

#include "SFML/Graphics.hpp"
#include "../../Base/Node.h"

class Text : public Node {
public:
    static std::shared_ptr<Text>
    create(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0);

    explicit Text(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0) : Node(
            parent, node_id, render_priority) {}

    static void setup(const std::shared_ptr<Text> &node);

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    void set_font(const std::string &path);

    void set_character_size(int new_character_size);

    void set_text(const std::string &new_text);

    void set_color(const sf::Color &new_color);

    void set_smooth(bool smooth);

private:
    void update_text();

    sf::VertexArray vertices;
    sf::Color color;
    sf::Font font;
    int character_size;
    std::string text;
};


#endif //LOGISTICHELL_TEXT_H
