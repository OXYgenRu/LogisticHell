//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINT_H
#define LOGISTICHELL_BLUEPRINT_H

#include <SFML/Graphics/View.hpp>
#include "../BlueprintComponent/BlueprintComponent.h"
#include "memory"

class Blueprint : public std::enable_shared_from_this<Blueprint> {
public:
    explicit Blueprint(sf::Vector2i grid_size, bool is_unit, int rotation);

    std::shared_ptr<BlueprintComponent> add_component();

    std::shared_ptr<BlueprintComponent> get_component(sf::Vector2i position);

    bool is_cell_exist(sf::Vector2i position) const;

    sf::Vector2i grid_size;

    std::vector<std::shared_ptr<BlueprintComponent>> components;

    bool as_unit;
};


#endif //LOGISTICHELL_BLUEPRINT_H
