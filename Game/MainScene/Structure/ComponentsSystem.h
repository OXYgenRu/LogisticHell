//
// Created by EgorRychkov on 04.08.2025.
//

#ifndef LOGISTICHELL_COMPONENTSSYSTEM_H
#define LOGISTICHELL_COMPONENTSSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "Component.h"

class GameWorld;

class ComponentsSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<Component>> components;
    unsigned int max_component_id{};
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<ComponentsSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit ComponentsSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void
    setup(const std::shared_ptr<ComponentsSystem> &node, const std::shared_ptr<GameWorld> &world);

    std::shared_ptr<Component> create_component(const std::shared_ptr<Structure> &structure);

    void destroy_component(const std::shared_ptr<Component> &component);

    void delete_component(const std::shared_ptr<Component> &component);
};


#endif //LOGISTICHELL_COMPONENTSSYSTEM_H
