//
// Created by EgorRychkov on 16.05.2025.
//

#ifndef LOGISTICHELL_ANCHOR_H
#define LOGISTICHELL_ANCHOR_H

#include "SFML/Graphics.hpp"

enum class AnchorBinding {
    LeftUp,
    CenterUp,
    RightUp,
    RightCenter,
    RightDown,
    CenterDown,
    LeftDown,
    LeftCenter,
    Center
};

enum class AnchorType {
    Relative,
    Absolute
};

class Anchor {
public:
    Anchor() {
        this->anchor_binding = AnchorBinding::LeftUp;
        this->anchor_type = AnchorType::Absolute;
        this->space_position = {0, 0};
        this->space_size = {1, 1};
        this->calculate_anchor_parameters();
    }

    Anchor(AnchorBinding anchor_binding, AnchorType anchor_type,
           sf::Vector2f space_position,
           sf::Vector2f space_size) {
        this->anchor_binding = anchor_binding;
        this->anchor_type = anchor_type;
        this->space_position = space_position;
        this->space_size = space_size;
        this->calculate_anchor_parameters();
    }

    void set_space(sf::Vector2f &new_space_position, sf::Vector2f &new_space_size) {
        this->space_position = new_space_position;
        this->space_size = new_space_size;
    }

    void set_anchor_binding(AnchorBinding &new_anchor_binding) {
        this->anchor_binding = new_anchor_binding;
        this->calculate_anchor_parameters();
    }

    void set_anchor_type(AnchorType &new_anchor_type) {
        this->anchor_type = new_anchor_type;
        this->calculate_anchor_parameters();
    }

    sf::Vector2f get_position(sf::Vector2f &position) const {
        switch (this->anchor_type) {
            case AnchorType::Absolute:
                return {position.x + anchor_position.x,
                        position.y + anchor_position.y};
            case AnchorType::Relative:
                return {position.x * this->space_size.x + anchor_position.x,
                        position.y * this->space_size.y + anchor_position.y};
        }
        return {0, 0};
    }

private:
    void calculate_anchor_parameters() {
        switch (this->anchor_binding) {
            case AnchorBinding::Center:
                this->anchor_position = this->space_position + this->space_size / float(2);
                break;
            case AnchorBinding::LeftUp:
                this->anchor_position = this->space_position;
                break;
            case AnchorBinding::CenterUp:
                this->anchor_position = {space_position.x + space_size.x / 2, space_position.y};
                break;
            case AnchorBinding::RightUp:
                this->anchor_position = {space_position.x + space_size.x, space_position.y};
                break;
            case AnchorBinding::RightCenter:
                this->anchor_position = {space_position.x + space_size.x, space_position.y + space_size.y / 2};
                break;
            case AnchorBinding::RightDown:
                this->anchor_position = {space_position.x + space_size.x, space_position.y + space_size.y};
                break;
            case AnchorBinding::CenterDown:
                this->anchor_position = {space_position.x + space_size.x / 2, space_position.y + space_size.y};
                break;
            case AnchorBinding::LeftDown:
                this->anchor_position = {space_position.x, space_position.y + space_size.y};
                break;
            case AnchorBinding::LeftCenter:
                this->anchor_position = {space_position.x, space_position.y + space_size.y / 2};
                break;
        }
    }

    AnchorBinding anchor_binding;
    AnchorType anchor_type;
    sf::Vector2f anchor_position;
    sf::Vector2f space_position;
    sf::Vector2f space_size;

};

#endif //LOGISTICHELL_ANCHOR_H
