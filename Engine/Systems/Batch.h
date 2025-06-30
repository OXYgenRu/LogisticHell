//
// Created by EgorRychkov on 22.06.2025.
//

#ifndef LOGISTICHELL_BATCH_H
#define LOGISTICHELL_BATCH_H

#include "SFML/Graphics.hpp"
#include "../EngineContext.h"


class Batch {
private:
    sf::VertexArray vertices;
    sf::RenderStates states;
public:

    explicit Batch();

    void add_vertices(const sf::VertexArray &new_vertices, const sf::Transform &transform);

    void flush(EngineContext &ctx);

    void set_texture(const sf::Texture  &new_texture,EngineContext &ctx);
};


#endif //LOGISTICHELL_BATCH_H
