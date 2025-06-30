//
// Created by EgorRychkov on 21.06.2025.
//

#include "StructuresSystem.h"
#include "../../../Engine/Nodes/UI/Rectangle.h"
#include "../MainScene.h"

StructuresSystem::StructuresSystem(const std::shared_ptr<MainScene> &scene, float block_side_size) {
    this->scene = scene;
    this->block_side_size = block_side_size;
}

void StructuresSystem::create_structure(std::shared_ptr<Blueprint> &blueprint, const sf::Vector2f &dock_position,
                                        EngineContext &ctx) {
    std::shared_ptr<Structure> new_structure = std::make_shared<Structure>(blueprint);
    float pixels_per_meter = this->scene.lock()->world->pixel_per_meter;
    this->structures.push_back(new_structure);
    for (auto &blueprint_component: blueprint->components) {
        std::shared_ptr<Component> new_component = Component::create(scene.lock()->world, new_structure);
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
        new_component->rigid_body = RigidBody::create(scene.lock()->world, new_def);
        for (int i = 0; i < blueprint->grid_size.y; i++) {
            for (int j = 0; j < blueprint->grid_size.x; j++) {
                if (blueprint_component->get_block({j, i}).type == BlockType::BusyAttachable) {
                    b2ShapeDef shape_def = b2DefaultShapeDef();
                    shape_def.density = 300.0f;
                    shape_def.material.friction = 0.3f;
                    new_component->create_block({j, i}, blueprint_component->get_block({j, i}), block_side_size,
                                                new_component);
                }
            }
        }
    }
    for (std::shared_ptr<UnitProperties> &blueprint_unit: blueprint->get_units_properties()) {
        std::shared_ptr<Unit> new_unit = std::make_shared<Unit>();
        new_unit->set_unit_behavior(blueprint_unit->get_behavior());
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
                    auto new_quad = UnitRenderQuad::create(new_structure->components[i], ctx, feature.texture_name,
                                                           {feature.anchor_block.x,
                                                            -feature.anchor_block.y},
                                                           feature.position,
                                                           feature.vertices, feature.angle,
                                                           block_side_size * scene.lock()->world->pixel_per_meter,
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
                    joint.component_block_a)->get_component()->rigid_body;
            std::shared_ptr<RigidBody> body_b = new_structure->units[j]->get_block(
                    joint.component_block_b)->get_component()->rigid_body;
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
    for(auto &component : new_structure->components){
        component->set_position(component->rigid_body->get_position());
        component->set_rotation(component->rigid_body->get_rotation());
        component->set_origin(component->rigid_body->get_origin());
    }
}