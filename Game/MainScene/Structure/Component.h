//
// Created by EgorRychkov on 11.06.2025.
//

#ifndef LOGISTICHELL_COMPONENT_H
#define LOGISTICHELL_COMPONENT_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Physics/RigidBody.h"
#include "../../../Engine/Nodes/Physics/CollisionPolygon.h"
#include "UnitRenderQuad.h"
#include "ComponentBlock.h"

class Structure;

class Component : public Node {
public:
    static std::shared_ptr<Component> create(const std::shared_ptr<Structure> &structure, int render_priority = 0);

    explicit Component(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    std::shared_ptr<RigidBody> rigid_body;
    std::vector<std::vector<std::shared_ptr<CollisionPolygon>>> collision_blocks;
    std::vector<std::vector<std::shared_ptr<ComponentBlock>>> blocks;
    std::weak_ptr<Structure> structure;
};


#endif //LOGISTICHELL_COMPONENT_H
