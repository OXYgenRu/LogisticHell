//
// Created by EgorRychkov on 06.05.2025.
//

#include "Atlas.h"

bool compare_by_width(const std::pair<std::string, sf::Image> &a, const std::pair<std::string, sf::Image> &b) {
    return a.second.getSize().y < b.second.getSize().y;
}


Atlas::Atlas(sf::Vector2i atlas_size) {
    this->atlas.create(atlas_size.x, atlas_size.y, sf::Color(0, 0, 0));
}

void Atlas::register_texture(const std::string &id, const std::string &image_name) {
    sf::Image image;
    if (!image.loadFromFile(image_name)) {
        throw std::runtime_error("Image doesnt exist");
    }

    this->images.emplace_back(id, image);
}

void Atlas::build() {
    std::sort(this->images.begin(), this->images.end(), compare_by_width);
    sf::Vector2i position = {0, 0};
    int height_step = 0;
    for (auto &element: this->images) {
        sf::Vector2u size = element.second.getSize();
        if (position.x + size.x >= this->atlas.getSize().x) {
            position = {0, position.y + height_step};
            height_step = int(size.y);
        }
        if (position.y + size.y >= this->atlas.getSize().y) {
            throw std::runtime_error("Atlas height overflow!");
        }

        atlas.copy(element.second, position.x, position.y);
        position.x += int(size.x);
    }
    atlas.saveToFile("atlas.png");
}