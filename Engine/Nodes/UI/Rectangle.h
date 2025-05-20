//
// Created by EgorRychkov on 18.05.2025.
//

#ifndef LOGISTICHELL_RECTANGLE_H
#define LOGISTICHELL_RECTANGLE_H

#include "../Base/ContentNode.h"
#include "Anchor.h"
#include "../Render/Shapes/TexturedQuad.h"

namespace UI {
    class Rectangle : public ContentNode {
    public:
        static std::shared_ptr<Rectangle>
        create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_position, sf::Vector2f space_size,
               AnchorType anchor_type = AnchorType::Relative, AnchorBinding anchor_binding = AnchorBinding::LeftUp,
               int render_priority = 0);

        explicit Rectangle(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                         render_priority) {}

        static void setup(std::shared_ptr<Rectangle> &node, sf::Vector2f &space_position, sf::Vector2f &space_size,
                          AnchorType anchor_type,
                          AnchorBinding anchor_binding);

        void set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right);

        void set_texture(const std::string &new_texture_name, EngineContext &ctx);

        void set_color(sf::Color color);

        void render(EngineContext &ctx) override;

    private:
        sf::RectangleShape polygon;
        Anchor anchor;
        sf::Vector2f top_left;
        sf::Vector2f bottom_right;
    };
}

#endif //LOGISTICHELL_RECTANGLE_H
