//
// Created by EgorRychkov on 21.06.2025.
//

#ifndef LOGISTICHELL_STRUCTURESSYSTEM_H
#define LOGISTICHELL_STRUCTURESSYSTEM_H

#include "vector"
#include "memory"
#include "Structure.h"
#include "StructuresSystem.h"

class MainScene;

class StructuresSystem : public Node {
public:
    static std::shared_ptr<StructuresSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<MainScene> &scene, float block_side_size,
           const std::string &node_id,
           int render_priority = 0);

    explicit StructuresSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<StructuresSystem> &node, const std::shared_ptr<MainScene> &scene,
                      float block_side_size);

    void create_structure(std::shared_ptr<Blueprint> &blueprint, const sf::Vector2f &dock_position, EngineContext &ctx);

    void crete_component_block(const sf::Vector2i &position, BlueprintBlock &block,
                               const std::shared_ptr<Component> &component) const;

    void destroy_structure(const std::shared_ptr<Structure> &structure);

    void update(EngineContext &ctx) override;

    std::vector<std::shared_ptr<Structure>> structures;
    std::weak_ptr<MainScene> scene;
    float block_side_size;
};


#endif //LOGISTICHELL_STRUCTURESSYSTEM_H
