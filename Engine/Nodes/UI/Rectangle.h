//
// Created by EgorRychkov on 18.05.2025.
//

#ifndef LOGISTICHELL_RECTANGLE_H
#define LOGISTICHELL_RECTANGLE_H

#include "../Base/Node.h"
#include "Anchor.h"
#include "../Render/Shapes/TexturedQuad.h"

namespace UI {
    class Rectangle : public Node {
    public:
        static std::shared_ptr<Rectangle>
        create(const std::shared_ptr<Node> &parent, int render_priority = 0);

        explicit Rectangle(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent,
                                                                                                render_priority) {}

        static void setup(std::shared_ptr<Rectangle> &node);

        void set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right);

        void set_texture(const std::string &new_texture_name, EngineContext &ctx);

        void set_color(sf::Color color);

        void render(EngineContext &ctx, sf::RenderStates &states) override;

    private:
        sf::RectangleShape polygon;
        sf::Vector2f top_left;
        sf::Vector2f bottom_right;
    };
}

#endif //LOGISTICHELL_RECTANGLE_H
