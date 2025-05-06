//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_TEXT_H
#define LOGISTICHELL_TEXT_H

#include "SFML/Graphics.hpp"
#include "../../Base/ContentNode.h"

class Text : public ContentNode {
public:
    static std::shared_ptr<Text> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit Text(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                render_priority) {}

    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    void set_font(const std::string &path);


    sf::Font font;
    sf::Text text;
};


#endif //LOGISTICHELL_TEXT_H
