//
// Created by EgorRychkov on 28.04.2025.a
//

#include "Structure.h"

std::shared_ptr<Structure>
Structure::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<World> world, sf::Vector2f position,
                  sf::Vector2i grid_size, float cell_size,
                  int render_priority,
                  int render_priority_layers) {
    auto node = std::make_shared<Structure>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Structure::setup(node, world, position, grid_size, cell_size);
    if (parent != nullptr) {
        parent->add_node(node);
    }
    return node;
}

void Structure::setup(std::shared_ptr<Structure> node, std::shared_ptr<World> world, sf::Vector2f position,
                      sf::Vector2i grid_size, float cell_size) {
    node->position = position;
    node->world = world;
    node->grid = Grid::create(node, grid_size, cell_size, node);

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = b2Vec2({0, 0});

    node->components.push_back(Component::create(node, node));
//    node->grid->grid_cells[0][0]->textured_quad->set_texture("blocks/TestConstructionBlock.png",ctx);
    node->components[0]->grid->grid_cells[0][0] = node->grid->grid_cells[0][0];
}
