//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_UNITSSYSTEM_H
#define LOGISTICHELL_UNITSSYSTEM_H

#include "Unit.h"

class GameWorld;

class UnitsSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<Unit>> units;
    unsigned int max_unit_id{};
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<UnitsSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world, const std::string &node_id,
           int render_priority = 0);

    explicit UnitsSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<UnitsSystem> &node, const std::shared_ptr<GameWorld> &world);

    void update(EngineContext &ctx) override;

    std::shared_ptr<Unit> create_unit(const sf::Vector2i &position, int rotation,
                                      const unsigned int &unit_index);

    std::shared_ptr<Unit> get_unit(const unsigned int &unit_id);
};

#endif //LOGISTICHELL_UNITSSYSTEM_H
