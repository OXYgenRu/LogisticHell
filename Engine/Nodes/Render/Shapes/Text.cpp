//
// Created by EgorRychkov on 20.04.2025.
//

#include "Text.h"
#include "../../Base/Node.h"
#include "../../../Application.h"

std::shared_ptr<Text> Text::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<Text>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void Text::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->window->draw(this->text, states);
}

void Text::update(EngineContext &ctx) {

}

int Text::get_node_type() const {
    return 8;
}

void Text::set_font(const std::string &path) {
    if (!this->font.loadFromFile(path)) {
        exit(0);
    }
    this->text.setFont(this->font);
}