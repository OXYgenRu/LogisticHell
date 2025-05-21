//
// Created by EgorRychkov on 16.05.2025.
//

#ifndef LOGISTICHELL_UIPOLYGON_H
#define LOGISTICHELL_UIPOLYGON_H


#include "../Base/ContentNode.h"
#include "Anchor.h"

class UIPolygon : public ContentNode {
public:
    static std::shared_ptr<UIPolygon>
    create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_size,
           AnchorType anchor_type = AnchorType::Relative, AnchorBinding anchor_binding = AnchorBinding::LeftUp,
           int render_priority = 0);

    explicit UIPolygon(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                     render_priority) {}

    static void setup(std::shared_ptr<UIPolygon> &node, sf::Vector2f &space_size,
                      AnchorType anchor_type,
                      AnchorBinding anchor_binding);

    void set_polygon(std::vector<sf::Vector2f> &new_polygon);

    void set_color(sf::Color color);

    void render(EngineContext &ctx, sf::RenderStates &states) override;

private:
    std::vector<sf::Vector2f> vertices;
    Anchor anchor;
    sf::ConvexShape polygon;
};


#endif //LOGISTICHELL_UIPOLYGON_H
