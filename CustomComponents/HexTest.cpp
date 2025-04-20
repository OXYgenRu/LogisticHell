//
// Created by EgorRychkov on 20.04.2025.
//
#include "cmath"
#include "HexTest.h"
#include "../Engine/Nodes/Base/ContainerNode.h"
#include "../Engine/Application.h"

std::shared_ptr<HexTest> HexTest::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<HexTest>(parent, render_priority);
    parent->add_node(node);

    const int texSize = 128;

    node->renderTexture.create(texSize, texSize);
    node->renderTexture.clear(sf::Color(200, 180, 140));
    node->renderTexture.display();

    node->hex = sf::VertexArray(sf::TriangleFan, 8);

    sf::Vector2f center(400.f, 300.f); // Центр шестиугольника на экране
    float radius = 10.f;

    // Центральная вершина
    node->hex[0].position = center;
    node->hex[0].texCoords = sf::Vector2f(texSize / 2.f, texSize / 2.f);

    // Вершины по кругу
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60.f * 3.14159265f / 180.f;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        node->hex[i + 1].position = sf::Vector2f(x, y);

        float tx = texSize / 2.f + radius * std::cos(angle);
        float ty = texSize / 2.f + radius * std::sin(angle);
        node->hex[i + 1].texCoords = sf::Vector2f(tx, ty);
    }
    float angle = 0 * 60.f * 3.14159265f / 180.f;
    float x = center.x + radius * std::cos(angle);
    float y = center.y + radius * std::sin(angle);
    node->hex[6 + 1].position = sf::Vector2f(x, y);

    float tx = texSize / 2.f + radius * std::cos(angle);
    float ty = texSize / 2.f + radius * std::sin(angle);
    node->hex[6 + 1].texCoords = sf::Vector2f(tx, ty);
    return node;
}


void HexTest::render(EngineContext &ctx) {
    sf::RenderStates states;
    states.texture = &renderTexture.getTexture();
    ctx.app->window->draw(hex, states);
}

void HexTest::update(EngineContext &ctx) {

}
