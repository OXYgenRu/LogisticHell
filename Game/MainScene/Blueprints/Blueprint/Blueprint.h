//
// Created by EgorRychkov on 03.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINT_H
#define LOGISTICHELL_BLUEPRINT_H

#include <SFML/Graphics/View.hpp>
#include "../BlueprintComponent/BlueprintComponent.h"
#include "../UnitProperties/UnitProperties.h"
#include "memory"
#include "Utils.h"

class Blueprint : public std::enable_shared_from_this<Blueprint> {
public:
    explicit Blueprint(sf::Vector2i grid_size,  int rotation);

    std::shared_ptr<BlueprintComponent> add_component();

    std::shared_ptr<BlueprintComponent> get_component(sf::Vector2i position) const;

    bool is_block_empty(sf::Vector2i position);

    bool is_cell_exist(sf::Vector2i position) const;

    sf::Vector2i grid_size;

    std::vector<std::shared_ptr<BlueprintComponent>> components;

    void set_unit_properties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &new_properties);

    std::shared_ptr<UnitProperties> get_unit_properties(const sf::Vector2i &position) const;

    std::vector<std::shared_ptr<UnitProperties>> &get_units_properties();

    void add_unit_properties(const std::shared_ptr<UnitProperties> &new_properties);

private:
    std::unordered_map<sf::Vector2i, std::shared_ptr<UnitProperties>> units_properties;
    std::vector<std::shared_ptr<UnitProperties>> units;
};

#endif //LOGISTICHELL_BLUEPRINT_H
