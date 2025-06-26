//
// Created by EgorRychkov on 22.06.2025.
//

#include "Batch.h"
#include "../Application.h"

Batch::Batch() {
    this->vertices.setPrimitiveType(sf::Quads);
}


void Batch::add_vertices(const sf::VertexArray &new_vertices, const sf::Transform &transform) {
    for (int i = 0; i < new_vertices.getVertexCount(); i++) {
        this->vertices.append(sf::Vertex(transform.transformPoint(new_vertices[i].position), new_vertices[i].color,
                                         new_vertices[i].texCoords));
    }
}


void Batch::flush(EngineContext &ctx) {
    ctx.app->window->draw(this->vertices, this->states);
    this->vertices.clear();

}

void Batch::set_texture(sf::Texture *new_texture) {
    this->states.texture = new_texture;
}