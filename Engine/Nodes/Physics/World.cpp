//
// Created by EgorRychkov on 24.04.2025.
//

#include "World.h"
#include "box2d/box2d.h"
#include "../Base/ContainerNode.h"

std::shared_ptr<World>
World::create(std::shared_ptr<ContainerNode> parent, b2Vec2 gravity, float pixel_per_meter, int render_priority,
              int render_priority_layers) {
    auto node = std::make_shared<World>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = gravity;
    node->world_id = b2CreateWorld(&world_def);
    node->pixel_per_meter = pixel_per_meter;
    parent->add_node(node);
    return node;
}

