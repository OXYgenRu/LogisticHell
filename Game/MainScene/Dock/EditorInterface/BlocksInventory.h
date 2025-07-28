//
// Created by EgorRychkov on 22.05.2025.
//

#ifndef LOGISTICHELL_BLOCKSINVENTORY_H
#define LOGISTICHELL_BLOCKSINVENTORY_H


#include "../../../../Engine/Nodes/Base/Node.h"
#include "../../../../Engine/Nodes/UI/VerticalList.h"

class Dock;

class GameWorld;

class BlocksInventory : public Node {
public:
    static std::shared_ptr<BlocksInventory>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
           const sf::Vector2f &container_size, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);


    explicit BlocksInventory(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}

    static void
    setup(const std::shared_ptr<BlocksInventory> &node, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
          const sf::Vector2f &container_size, const std::shared_ptr<GameWorld> &world);

private:
    std::weak_ptr<Dock> dock;
    std::weak_ptr<GameWorld> world;
    std::shared_ptr<UI::VerticalList> vertical_list;
};


#endif //LOGISTICHELL_BLOCKSINVENTORY_H
