//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_SPRITE_H
#define LOGISTICHELL_SPRITE_H

#include "../../Base/ContentNode.h"

class Sprite : public ContentNode {
public:
    static std::shared_ptr<Sprite> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit Sprite(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                  render_priority) {}


    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    sf::Sprite sprite;
};


#endif //LOGISTICHELL_SPRITE_H
