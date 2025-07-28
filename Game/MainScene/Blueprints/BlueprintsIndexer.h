//
// Created by EgorRychkov on 27.07.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTSINDEXER_H
#define LOGISTICHELL_BLUEPRINTSINDEXER_H

#include <unordered_map>
#include "iostream"

class BlueprintsIndexer {
public:
    BlueprintsIndexer();

    unsigned int register_new_blueprint_name(const std::string &new_name);

    unsigned int get_blueprint_index(const std::string &name);

    std::string &get_blueprint_name(const unsigned int &index);

private:
    std::unordered_map<std::string, unsigned int> blueprints_indices;
    std::unordered_map<unsigned int, std::string> blueprints_names;
    unsigned int max_blueprint_index{};
};

#endif //LOGISTICHELL_BLUEPRINTSINDEXER_H
