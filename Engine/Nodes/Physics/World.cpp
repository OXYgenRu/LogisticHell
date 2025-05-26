//
// Created by EgorRychkov on 24.04.2025.
//

#include "World.h"
#include "box2d/box2d.h"
#include "../Base/Node.h"

std::shared_ptr<World>
World::create(const std::shared_ptr<Node> &parent, b2Vec2 gravity, float pixel_per_meter, int render_priority) {
    auto node = std::make_shared<World>(parent, render_priority);
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = gravity;
    node->world_id = b2CreateWorld(&world_def);
    node->pixel_per_meter = pixel_per_meter;
    parent->add_node(node);
    return node;
}

