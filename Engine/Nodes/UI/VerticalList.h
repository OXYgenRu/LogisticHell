//
// Created by EgorRychkov on 21.05.2025.
//

#ifndef LOGISTICHELL_VERTICALLIST_H
#define LOGISTICHELL_VERTICALLIST_H

#include "../Base/Node.h"
#include "Button.h"
#include "../../../Engine/Nodes/Render/Shapes/Text.h"

namespace UI {
    class VerticalList;

    class ListItem : public Node {
    public:
        static std::shared_ptr<ListItem>
        create(const std::shared_ptr<VerticalList> &parent, EngineContext &ctx, const sf::Vector2f &item_size,
               const std::string &node_id,
               int render_priority = 0);


        explicit ListItem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
                : Node(parent, node_id, render_priority) {}

        static void setup(std::shared_ptr<ListItem> &node, EngineContext &ctx, const sf::Vector2f &item_size);

        std::shared_ptr<UI::Button> button;
        std::shared_ptr<Node> text_layer;
        std::shared_ptr<Text> text;
    };

    class VerticalList : public Node {
    public:
        static std::shared_ptr<VerticalList>
        create(const std::shared_ptr<Node> &parent, EngineContext &ctx,
               const sf::Vector2f &container_size, int list_size,const std::string &node_id,
               int render_priority = 0);


        explicit VerticalList(const std::shared_ptr<Node> &parent,const std::string &node_id, int render_priority = 0)
                : Node(parent,node_id, render_priority) {}

        static void setup(std::shared_ptr<VerticalList> &node, EngineContext &ctx, const sf::Vector2f &container_size,
                          int list_size);

        int get_list_size() const;

        std::shared_ptr<ListItem> &get_item(int index);

    private:
        std::vector<std::shared_ptr<ListItem>> items;
    };

}


#endif //LOGISTICHELL_VERTICALLIST_H
