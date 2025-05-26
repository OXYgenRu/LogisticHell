//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_WORLD_H
#define LOGISTICHELL_WORLD_H

#include "../Base/Node.h"
#include "box2d/box2d.h"

class World : public Node {
public:
    static std::shared_ptr<World>
    create(const std::shared_ptr<Node> &parent, b2Vec2 gravity, float pixel_per_meter, int render_priority = 0);


    explicit World(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    b2WorldId world_id;
    float pixel_per_meter;
};


#endif //LOGISTICHELL_WORLD_H
