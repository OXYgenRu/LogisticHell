//
// Created by EgorRychkov on 15.04.2025.
//

#ifndef LOGISTICHELL_POLYGON_H
#define LOGISTICHELL_POLYGON_H

#include "../../Base/Node.h"
#include "../../../EngineContext.h"

class Polygon : public Node {
public:
    static std::shared_ptr<Polygon> create(const std::shared_ptr<Node> &parent, int render_priority = 0);

    explicit Polygon(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent, render_priority) {}

    void set_polygon(std::vector<sf::Vector2<float>> &new_polygon);

    void set_polygon();

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    sf::ConvexShape polygon;
};


#endif //LOGISTICHELL_POLYGON_H
