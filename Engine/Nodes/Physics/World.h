//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_WORLD_H
#define LOGISTICHELL_WORLD_H

#include "../Base/Node.h"
#include "box2d/box2d.h"
#include "RevoluteJoint.h"

struct BodyIdHash {
    std::size_t operator()(const b2BodyId &id) const noexcept {
        std::size_t h1 = std::hash<int32_t>{}(id.index1);
        std::size_t h2 = std::hash<uint16_t>{}(id.world0);
        std::size_t h3 = std::hash<uint16_t>{}(id.generation);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct BodyIdEqual {
    bool operator()(const b2BodyId &a, const b2BodyId &b) const noexcept {
        return a.index1 == b.index1 &&
               a.world0 == b.world0 &&
               a.generation == b.generation;
    }
};


class RigidBody;

class World : public Node {
public:
    static std::shared_ptr<World>
    create(const std::shared_ptr<Node> &parent, b2Vec2 gravity, float pixel_per_meter,  const std::string &node_id,int render_priority = 0);


    explicit World(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent,node_id, render_priority) {}

    ~World();

    void destroy();

    b2WorldId world_id;
    float pixel_per_meter;

};


#endif //LOGISTICHELL_WORLD_H
