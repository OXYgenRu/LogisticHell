//
// Created by EgorRychkov on 22.05.2025.
//

#ifndef LOGISTICHELL_BLOCKSINVENTORY_H
#define LOGISTICHELL_BLOCKSINVENTORY_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../../Engine/Nodes/UI/VerticalList.h"

class Dock;

class BlueprintLoader;

class BlocksInventory : public ContainerNode {
public:
    static std::shared_ptr<BlocksInventory>
    create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<Dock> &dock,
           const sf::Vector2f &container_size, std::shared_ptr<BlueprintLoader> &blueprint_loader,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit BlocksInventory(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContainerNode(parent,
                                                                                                             render_priority) {}

    static void setup(std::shared_ptr<BlocksInventory> &node, EngineContext &ctx, std::shared_ptr<Dock> &dock,
                      const sf::Vector2f &container_size, std::shared_ptr<BlueprintLoader> &blueprint_loader);

private:
    std::weak_ptr<Dock> dock;
    std::weak_ptr<BlueprintLoader> blueprint_loader;
    std::shared_ptr<UI::VerticalList> vertical_list;
};


#endif //LOGISTICHELL_BLOCKSINVENTORY_H
