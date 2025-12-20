//
// Created by EgorRychkov on 29.07.2025.
//

#ifndef LOGISTICHELL_BLOCKSSYSTEM_H
#define LOGISTICHELL_BLOCKSSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "ComponentBlock.h"
#include "../Blueprints/BlueprintComponent/BlueprintComponent.h"

class GameWorld;

class BlocksSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<ComponentBlock>> blocks;
    unsigned int max_block_id{};
    std::weak_ptr<GameWorld> world;
    float block_side_size;
public:
    static std::shared_ptr<BlocksSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world, float block_side_size,
           const std::string &node_id,
           int render_priority = 0);

    explicit BlocksSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void
    setup(const std::shared_ptr<BlocksSystem> &node, const std::shared_ptr<GameWorld> &world, float block_side_size);

    std::shared_ptr<ComponentBlock> create_block(const sf::Vector2i &position, BlueprintBlock &block,
                                                 const std::shared_ptr<Component> &component);

    std::shared_ptr<ComponentBlock> get_block(const unsigned int &block_id);

    void destroy_block(const std::shared_ptr<ComponentBlock> &block);

    void delete_block(const std::shared_ptr<ComponentBlock> &block);
};


#endif //LOGISTICHELL_BLOCKSSYSTEM_H
