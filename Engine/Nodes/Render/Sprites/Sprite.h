//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_SPRITE_H
#define LOGISTICHELL_SPRITE_H

#include "../../Base/Node.h"

class Sprite : public Node {
public:
    static std::shared_ptr<Sprite> create(const std::shared_ptr<Node> &parent, int render_priority = 0);

    explicit Sprite(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent,
                                                                                         render_priority) {}


    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    sf::Sprite sprite;
};


#endif //LOGISTICHELL_SPRITE_H
