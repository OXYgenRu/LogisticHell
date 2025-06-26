//
// Created by EgorRychkov on 12.06.2025.
//

#include "BuildingGrid.h"


std::shared_ptr<BuildingGrid>
BuildingGrid::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, float sf_cell_size,
                     const sf::Vector2i &grid_size, int render_priority) {
    auto node = std::make_shared<BuildingGrid>(parent, render_priority);
    setup(node, sf_cell_size, grid_size, ctx);
    parent->add_node(node);
    return node;
}


void BuildingGrid::setup(const std::shared_ptr<BuildingGrid> &node, float sf_cell_size,
                         const sf::Vector2i &grid_size, EngineContext &ctx) {
    node->sf_cell_size = sf_cell_size;
    node->grid_size = grid_size;
    node->grid_collider = UI::Collider::create(node);
    node->grid_collider->set_vertices(
            {sf::Vector2f(0, 0), sf::Vector2f(float(grid_size.x) * sf_cell_size, 0),
             sf::Vector2f(float(grid_size.x) * sf_cell_size, float(grid_size.y) * sf_cell_size),
             sf::Vector2f(0, float(grid_size.y) * sf_cell_size)});

    node->grid_collider->set_position(sf::Vector2f(-sf_cell_size / 2, -sf_cell_size / 2));
    node->render_features.resize(grid_size.y,
                                 std::vector<std::shared_ptr<Node>>(grid_size.x));
    node->preview_render_features.resize(grid_size.y,
                                         (std::vector<std::shared_ptr<Node>>(
                                                 grid_size.x)));
    node->mask.resize(grid_size.y, (std::vector<std::shared_ptr<TexturedQuad>>(grid_size.x)));
    for (int i = 0; i < grid_size.y; i++) {
        for (int j = 0; j < grid_size.x; j++) {
            node->render_features[i][j] = Node::create(node);
            node->render_features[i][j]->set_position(
                    {float(j) * sf_cell_size, float(grid_size.y - i - 1) * sf_cell_size});

            node->preview_render_features[i][j] = Node::create(node, 1);
            node->preview_render_features[i][j]->set_position(
                    {float(j) * sf_cell_size, float(grid_size.y - i - 1) * sf_cell_size});

            node->mask[i][j] = TexturedQuad::create(node, 2);
            node->mask[i][j]->set_position({float(j) * sf_cell_size - sf_cell_size / 2,
                                            float(grid_size.y - i - 1) * sf_cell_size - sf_cell_size / 2});
            node->mask[i][j]->set_quad({{0,            0},
                                        {0,            sf_cell_size},
                                        {sf_cell_size, sf_cell_size},
                                        {sf_cell_size, 0}});
            node->mask[i][j]->set_texture("empty_block", 0, ctx);
        }
    }
}

void BuildingGrid::add_render_feature(const UnitRenderFeature &new_feature,
                                      EngineContext &ctx) {
    auto new_quad = TexturedQuad::create(
            render_features[new_feature.anchor_block.y][new_feature.anchor_block.x], new_feature.render_priority);
    new_quad->set_texture(new_feature.texture_name, 0, ctx);
    new_quad->set_position({new_feature.position.x * sf_cell_size, -new_feature.position.y * sf_cell_size});
    for (int i = 0; i < 4; i++) {
        new_quad->quad[i].position = {new_feature.vertices[i].x  * sf_cell_size,-new_feature.vertices[i].y  * sf_cell_size};
    }
    new_quad->set_rotation(new_feature.angle);
}

void BuildingGrid::add_preview_render_feature(const UnitRenderFeature &new_feature, const sf::Vector2i &unit_position,
                                              EngineContext &ctx) {
    auto new_quad = TexturedQuad::create(
            preview_render_features[unit_position.y + new_feature.anchor_block.y][unit_position.x +
                                                                                  new_feature.anchor_block.x],
            new_feature.render_priority);
    new_quad->set_texture(new_feature.texture_name, 0, ctx);
    new_quad->set_position({new_feature.position.x * sf_cell_size, -new_feature.position.y * sf_cell_size});
    for (int i = 0; i < 4; i++) {
        new_quad->quad[i].position = {new_feature.vertices[i].x  * sf_cell_size,-new_feature.vertices[i].y  * sf_cell_size};
    }
    new_quad->set_rotation(new_feature.angle);
}

void BuildingGrid::set_mask(const std::string &texture_name, const sf::Vector2i &position, EngineContext &ctx) {
    mask[position.y][position.x]->set_texture(texture_name, 0, ctx);
}

void BuildingGrid::remove_features(const sf::Vector2i &position) {
    this->render_features[position.y][position.x]->clear_container();
}

void BuildingGrid::remove_preview_features(const sf::Vector2i &position) {
    this->preview_render_features[position.y][position.x]->clear_container();
}