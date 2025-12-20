//
// Created by EgorRychkov on 07.11.2025.
//

#ifndef LOGISTICHELL_ENTITYSYSTEM_H
#define LOGISTICHELL_ENTITYSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "Entity.h"

class GameWorld;

class EntitySystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<Entity>> entities;
    unsigned int max_entity_id{};
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<EntitySystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit EntitySystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<EntitySystem> &node, const std::shared_ptr<GameWorld> &world);

    std::shared_ptr<Entity>
    spawn(EngineContext &ctx, const sf::Vector2f &b2_position, const sf::Vector2f &b2_size, const float &density,
          const float &friction);
};


#endif //LOGISTICHELL_ENTITYSYSTEM_H
