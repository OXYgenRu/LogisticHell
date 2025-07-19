//
// Created by EgorRychkov on 13.07.2025.
//

#ifndef LOGISTICHELL_DOCKSSYSTEM_H
#define LOGISTICHELL_DOCKSSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "Dock.h"

class MainScene;

class DocksSystem : public Node {
private:
    std::weak_ptr<MainScene> weak_scene;
    std::vector<std::shared_ptr<DockSpawner>> spawners;
    std::shared_ptr<Dock> dock;
public:
    static std::shared_ptr<DocksSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<MainScene> &scene, const std::string &node_id,
           int render_priority = 0);

    explicit DocksSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {}

    static void setup(const std::shared_ptr<DocksSystem> &node, const std::shared_ptr<MainScene> &scene);

    void create_dock_spawner(EngineContext &ctx, const sf::Vector2f &position, const sf::Vector2i &grid_size,
                             float b2_block_side_size);

    void spawn_dock(EngineContext &ctx, const sf::Vector2f &position, const sf::Vector2i &grid_size,
                    float b2_block_side_size, const std::shared_ptr<Blueprint> &blueprint);


    std::shared_ptr<DockSpawner> find_nearest_dock(const sf::Vector2f &position);
};


#endif //LOGISTICHELL_DOCKSSYSTEM_H
