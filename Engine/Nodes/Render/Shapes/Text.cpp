//
// Created by EgorRychkov on 20.04.2025.
//

#include "Text.h"
#include "../../Base/Node.h"
#include "../../../Application.h"

std::shared_ptr<Text>
Text::create(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority) {
    auto node = std::make_shared<Text>(parent, node_id, render_priority);
    parent->add_node(node);
    Text::setup(node);
    return node;
}


void Text::setup(const std::shared_ptr<Text> &node) {
    node->character_size = 10;
    node->vertices.setPrimitiveType(sf::Quads);
    node->set_font("Minecraftia-Regular.ttf");
    node->set_character_size(24);
    node->font.setSmooth(false);
}

void Text::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->batch->set_texture(font.getTexture(character_size), ctx);
    ctx.app->batch->add_vertices(vertices, states.transform);

}

void Text::update(EngineContext &ctx) {

}

void Text::set_smooth(bool smooth) {
    font.setSmooth(smooth);
}

void Text::update_text() {
    vertices.clear();

    float x = 0.0f;
    float y = -font.getGlyph('A', character_size, false).bounds.top;

    for (char c: text) {
        if (c == '\n') {
            x = 0;
            y += font.getLineSpacing(character_size);
            continue;
        }
        const sf::Glyph &glyph = font.getGlyph(c, character_size, false);
        sf::FloatRect bounds = glyph.bounds;
        sf::IntRect textureRect = glyph.textureRect;

        float x0 = x + bounds.left;
        float y0 = y + bounds.top;
        float x1 = x0 + bounds.width;
        float y1 = y0 + bounds.height;

        auto u0 = static_cast<float>(textureRect.left);
        auto v0 = static_cast<float>(textureRect.top);
        auto u1 = static_cast<float>(textureRect.left + textureRect.width);
        auto v1 = static_cast<float>(textureRect.top + textureRect.height);


        vertices.append(sf::Vertex({x0, y0}, color, {u0, v0}));
        vertices.append(sf::Vertex({x1, y0}, color, {u1, v0}));
        vertices.append(sf::Vertex({x1, y1}, color, {u1, v1}));
        vertices.append(sf::Vertex({x0, y1}, color, {u0, v1}));

        x += glyph.advance;
    }
}

int Text::get_node_type() const {
    return 8;
}

void Text::set_font(const std::string &path) {
    if (!this->font.loadFromFile(path)) {
        throw std::runtime_error("Font loading error");
    }
    update_text();
}


void Text::set_character_size(int new_character_size) {
    this->character_size = new_character_size;
    update_text();
}

void Text::set_text(const std::string &new_text) {
    this->text = new_text;
    update_text();
}

void Text::set_color(const sf::Color &new_color) {
    this->color = new_color;
    update_text();
}