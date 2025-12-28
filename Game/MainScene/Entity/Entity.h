//
// Created by EgorRychkov on 07.11.2025.
//

#ifndef LOGISTICHELL_ENTITY_H
#define LOGISTICHELL_ENTITY_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Physics/RigidBody.h"

class GameWorld;

class Entity : public Node {
private:
    unsigned int entity_id;
    std::shared_ptr<RigidBody> rigid_body;
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<Entity>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<GameWorld> &world,
           const unsigned int &entity_id, const sf::Vector2f &b2_position, const sf::Vector2f &b2_size,
           const float &density, const float &friction,
           const std::string &node_id,
           int render_priority = 0);

    explicit Entity(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}

    static void
    setup(std::shared_ptr<Entity> &node, const std::shared_ptr<GameWorld> &world, const unsigned int &entity_id,
          const sf::Vector2f &b2_position, const sf::Vector2f &b2_size, const float &density, const float &friction);

    void update(EngineContext &ctx) override;

    unsigned int get_id();

    std::optional<sf::Vector2f> get_b2_position() const;

    std::optional<float> get_b2_rotation() const;
};


#endif //LOGISTICHELL_ENTITY_H
