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
#include "../../../Engine/Nodes/Physics/World.h"
#include "../Blueprints/BlueprintComponent/BlueprintComponent.h"
#include "../../../Engine/Nodes/UI/Collider.h"

class Structure;

class Component : public Node {
public:
    static std::shared_ptr<Component>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Structure> &structure, const std::string &node_id,
           int render_priority = 0);

    explicit Component(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}

    static void setup(std::shared_ptr<Component> &node, const std::shared_ptr<Structure> &structure);

    void update(EngineContext &ctx) override;

    ~Component();

    sf::Vector2i grid_size;
    std::shared_ptr<RigidBody> rigid_body;
    std::vector<std::vector<std::shared_ptr<CollisionPolygon>>> collision_blocks;
    std::vector<std::vector<std::shared_ptr<UI::Collider>>> colliders;
    std::vector<std::vector<std::shared_ptr<ComponentBlock>>> blocks;
    std::weak_ptr<Structure> structure;
};


#endif //LOGISTICHELL_COMPONENT_H
