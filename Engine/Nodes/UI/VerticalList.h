//
// Created by EgorRychkov on 21.05.2025.
//

#ifndef LOGISTICHELL_VERTICALLIST_H
#define LOGISTICHELL_VERTICALLIST_H

#include "../Base/ContainerNode.h"
#include "Button.h"
#include "../../../Engine/Nodes/Render/Shapes/Text.h"

namespace UI {
    class VerticalList;

    class ListItem : public ContainerNode {
    public:
        static std::shared_ptr<ListItem>
        create(std::shared_ptr<VerticalList> parent, EngineContext &ctx, const sf::Vector2f &item_size,
               int render_priority = 0,
               int render_priority_layers = 10
        );


        explicit ListItem(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
                : ContainerNode(parent, render_priority) {}

        static void setup(std::shared_ptr<ListItem> &node, EngineContext &ctx, const sf::Vector2f &item_size);

        std::shared_ptr<UI::Button> button;
        std::shared_ptr<ContainerNode> text_layer;
        std::shared_ptr<Text> text;
    };

    class VerticalList : public ContainerNode {
    public:
        static std::shared_ptr<VerticalList>
        create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx,
               const sf::Vector2f &container_size, int list_size,
               int render_priority = 0,
               int render_priority_layers = 10
        );


        explicit VerticalList(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
                : ContainerNode(parent, render_priority) {}

        static void setup(std::shared_ptr<VerticalList> &node, EngineContext &ctx, const sf::Vector2f &container_size,
                          int list_size);

        int get_list_size() const;

        std::shared_ptr<ListItem> &get_item(int index);

    private:
        std::vector<std::shared_ptr<ListItem>> items;
    };

}


#endif //LOGISTICHELL_VERTICALLIST_H
