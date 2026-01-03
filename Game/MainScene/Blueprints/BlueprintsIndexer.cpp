//
// Created by EgorRychkov on 27.07.2025.
//

#include "BlueprintsIndexer.h"

BlueprintsIndexer::BlueprintsIndexer() {}

unsigned int BlueprintsIndexer::register_new_blueprint_name(const std::string &new_name) {
    if (blueprints_indices.find(new_name) != blueprints_indices.end()) {
        throw std::runtime_error(
                "[BlueprintsIndexer::register_new_blueprint_name]:blueprints_indices: blueprint with name '" +
                new_name + "' already exists.");
    }
    blueprints_indices[new_name] = max_blueprint_index;
    blueprints_names[max_blueprint_index] = new_name;
    max_blueprint_index++;
    return max_blueprint_index - 1;
}

unsigned int BlueprintsIndexer::get_blueprint_index(const std::string &id) {
    if (blueprints_indices.find(id) == blueprints_indices.end()) {
        throw std::runtime_error(
                "[BlueprintsIndexer::get_blueprint_index]:blueprints_indices: unit name '" + id + "' not found.");
    }
    return blueprints_indices[id];
}

std::string &BlueprintsIndexer::get_blueprint_name(const unsigned int &index) {
    return blueprints_names[index];
}