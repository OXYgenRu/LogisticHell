//
// Created by EgorRychkov on 21.06.2025.
//

#include "StructuresSystem.h"
#include "../../../Engine/Nodes/UI/Rectangle.h"
#include "../MainScene.h"

std::shared_ptr<StructuresSystem>
StructuresSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                         float block_side_size, const std::string &node_id,
                         int render_priority) {
    auto node = std::make_shared<StructuresSystem>(parent, node_id, render_priority);
    StructuresSystem::setup(node, world, block_side_size);
    parent->add_node(node);
    return node;
}

void StructuresSystem::setup(const std::shared_ptr<StructuresSystem> &node, const std::shared_ptr<GameWorld> &world,
                             float block_side_size) {
    node->world = world;
    node->block_side_size = block_side_size;
}

std::shared_ptr<Structure>
StructuresSystem::create_structure(std::shared_ptr<Blueprint> &blueprint, const sf::Vector2f &dock_position,
                                   EngineContext &ctx) {
    unsigned int structure_id = max_structure_id++;
    std::weak_ptr<GameWorld> capture_weak_world = world;
    std::shared_ptr<Structure> new_structure = std::make_shared<Structure>(blueprint, structure_id);
    float pixels_per_meter = world.lock()->get_pixel_per_meter();
    this->structures[structure_id] = new_structure;
    for (auto &blueprint_component: blueprint->components) {
        std::shared_ptr<Component> new_component = world.lock()->get_components_system()->create_component(
                new_structure);
        new_component->set_render_priority(2);
        new_structure->components.push_back(new_component);
        b2BodyDef new_def = b2DefaultBodyDef();
        new_def.position = {float(dock_position.x) / pixels_per_meter, -(float(dock_position.y) / pixels_per_meter)};
        switch (blueprint_component->get_body_type()) {
            case ComponentBodyType::Dynamic:
                new_def.type = b2_dynamicBody;
                break;
            case ComponentBodyType::Static:
                new_def.type = b2_staticBody;
                break;
            case ComponentBodyType::Kinematic:
                new_def.type = b2_kinematicBody;
                break;
        }
        new_component->rigid_body = RigidBody::create(world.lock()->get_world(), new_def, "ComponentRigidBody");
        for (int i = 0; i < blueprint->grid_size.y; i++) {
            for (int j = 0; j < blueprint->grid_size.x; j++) {
                if (blueprint_component->get_block({j, i}).type == BlockType::BusyAttachable) {
                    world.lock()->get_blocks_system()->create_block({j, i}, blueprint_component->get_block({j, i}),
                                                                    new_component);
                    std::weak_ptr<Component> capture_component = new_component;
                    new_component->blocks[i][j]->collider->bind_on_key_release(
                            [capture_weak_world, capture_component](sf::Event &event, EngineContext &ctx,
                                                                    const sf::Vector2f &local_position) {
                                if (event.key.code == sf::Keyboard::Key::R) {
                                    auto locked_world = capture_weak_world.lock();
                                    std::shared_ptr<Component> component = capture_component.lock();
                                    std::shared_ptr<DockSpawner> spawner = locked_world->get_docks_system()->find_nearest_dock(
                                            component->get_position());
                                    locked_world->get_docks_system()->spawn_dock(ctx,
                                                                                 spawner->get_dock_position(),
                                                                                 spawner->get_grid_size(),
                                                                                 spawner->get_block_side_size(),
                                                                                 component->structure.lock()->blueprint);
                                    locked_world->get_structures_system()->destroy_structure(
                                            component->structure.lock());
                                }
                            });
                }
            }
        }
    }
    for (std::shared_ptr<UnitProperties> &blueprint_unit: blueprint->get_units_properties()) {
        std::shared_ptr<Unit> new_unit = world.lock()->get_units_system()->create_unit(blueprint_unit->position,
                                                                                       blueprint_unit->rotation,
                                                                                       blueprint_unit->get_unit_index());
        new_structure->units.push_back(new_unit);
    }
    for (int i = 0; i < blueprint->components.size(); i++) {
        for (int j = 0; j < blueprint->get_units_properties().size(); j++) {
            std::shared_ptr<UnitProperties> &blueprint_unit = blueprint->get_units_properties()[j];
            for (sf::Vector2i &position: blueprint_unit->get_unit_blocks()) {
                if (new_structure->components[i]->blocks[position.y][position.x] != nullptr) {
                    new_structure->components[i]->blocks[position.y][position.x]->set_unit(new_structure->units[j]);
                    new_structure->units[j]->add_block(new_structure->components[i]->blocks[position.y][position.x]);
                }
            }
            for (UnitRenderFeature &feature: blueprint_unit->get_render_features()) {
                if (new_structure->components[i]->blocks[feature.anchor_block.y][feature.anchor_block.x] != nullptr) {
                    auto new_quad = UnitRenderQuad::create(new_structure->components[i], ctx, feature.feature_name,
                                                           feature.texture_name,
                                                           {feature.anchor_block.x,
                                                            -feature.anchor_block.y},
                                                           feature.position,
                                                           feature.vertices, feature.angle,
                                                           block_side_size * world.lock()->get_pixel_per_meter(),
                                                           "RenderQuad",
                                                           feature.render_priority);

                    new_structure->components[i]->blocks[feature.anchor_block.y][feature.anchor_block.x]->add_render_quad(
                            new_quad);
                    new_structure->units[j]->set_render_feature(feature.feature_name, new_quad);
                }
            }
        }
    }
    for (int j = 0; j < blueprint->get_units_properties().size(); j++) {
        for (BlueprintJoints::RevoluteJoint &joint: blueprint->get_units_properties()[j]->get_revolute_joints()) {
            std::shared_ptr<RigidBody> body_a = new_structure->units[j]->get_block(
                    joint.component_block_a)->get_weak_component().lock()->rigid_body;
            std::shared_ptr<RigidBody> body_b = new_structure->units[j]->get_block(
                    joint.component_block_b)->get_weak_component().lock()->rigid_body;
            b2RevoluteJointDef joint_def = b2DefaultRevoluteJointDef();
            b2Vec2 world_point = {dock_position.x / pixels_per_meter, -dock_position.y / pixels_per_meter};
            world_point += {float(joint.block_position.x) * block_side_size,
                            float(joint.block_position.y) * block_side_size};
            joint_def.localAnchorA =
                    b2Body_GetLocalPoint(body_a->body_id, world_point);
            joint_def.localAnchorB =
                    b2Body_GetLocalPoint(body_b->body_id, world_point);
            new_structure->units[j]->set_joint(joint.joint_name,
                                               std::make_shared<RevoluteJoint>(body_a, body_b, joint_def));
        }
    }
    for (auto &component: new_structure->components) {
        component->set_position(component->rigid_body->get_position());
        component->set_rotation(component->rigid_body->get_rotation());
        component->set_origin(component->rigid_body->get_origin());
        b2Body_SetAngularDamping(component->rigid_body->body_id, 1);
        b2Body_SetLinearDamping(component->rigid_body->body_id, 1);
    }
    return new_structure;
}


void StructuresSystem::update(EngineContext &ctx) {
//    for (auto &structure: structures) {
//        for (std::shared_ptr<Unit> &unit: structure->units) {
//            unit->get_behavior()->update(ctx, unit->api);
//        }
//    }
}


void StructuresSystem::destroy_structure(const std::shared_ptr<Structure> &structure) {
    this->delete_structure(structure);
    for (std::shared_ptr<Component> &component: structure->components) {
        for (int y = 0; y < component->grid_size.y; y++) {
            for (int x = 0; x < component->grid_size.x; x++) {
                if (component->blocks[y][x] != nullptr) {
                    world.lock()->get_blocks_system()->delete_block(component->blocks[y][x]);
                }
            }
        }
        world.lock()->get_components_system()->delete_component(component);
        world.lock()->get_world()->delete_node(component->rigid_body);
        world.lock()->delete_node(component);
    }
    for (std::shared_ptr<Unit> &unit: structure->units) {
        world.lock()->get_units_system()->destroy_unit(unit);
    }
}

void StructuresSystem::delete_structure(const std::shared_ptr<Structure> &structure) {
    auto it = this->structures.find(structure->get_structure_id());
    if (it == this->structures.end()) {
        throw std::runtime_error("Deleting structures not found");
    }
    this->structures.erase(it);
}