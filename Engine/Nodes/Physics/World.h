//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_WORLD_H
#define LOGISTICHELL_WORLD_H

#include "../Base/ContainerNode.h"
#include "box2d/box2d.h"

class World : public ContainerNode {
public:
    static std::shared_ptr<World>
    create(std::shared_ptr<ContainerNode> parent, b2Vec2 gravity, float pixel_per_meter, int render_priority = 0,
           int render_priority_layers = 10);


    explicit World(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    b2WorldId world_id;
    float pixel_per_meter;
};


#endif //LOGISTICHELL_WORLD_H
