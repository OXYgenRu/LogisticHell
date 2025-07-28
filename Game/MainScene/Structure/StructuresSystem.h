//
// Created by EgorRychkov on 21.06.2025.
//

#ifndef LOGISTICHELL_STRUCTURESSYSTEM_H
#define LOGISTICHELL_STRUCTURESSYSTEM_H

#include "vector"
#include "memory"
#include "Structure.h"
#include "StructuresSystem.h"

class GameWorld;

class StructuresSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<Structure>> structures;
    unsigned int max_structure_id{};
public:
    static std::shared_ptr<StructuresSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world, float block_side_size,
           const std::string &node_id,
           int render_priority = 0);

    explicit StructuresSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<StructuresSystem> &node, const std::shared_ptr<GameWorld> &world,
                      float block_side_size);

    unsigned int
    create_structure(std::shared_ptr<Blueprint> &blueprint, const sf::Vector2f &dock_position, EngineContext &ctx);

    void crete_component_block(const sf::Vector2i &position, BlueprintBlock &block,
                               const std::shared_ptr<Component> &component) const;

    void destroy_structure(const unsigned int &structure_id);

    void update(EngineContext &ctx) override;


    std::weak_ptr<GameWorld> world;
    float block_side_size;
};


#endif //LOGISTICHELL_STRUCTURESSYSTEM_H
