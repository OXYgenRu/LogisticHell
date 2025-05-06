//
// Created by EgorRychkov on 06.05.2025.
//

#ifndef LOGISTICHELL_ATLAS_H
#define LOGISTICHELL_ATLAS_H

#include "SFML/Graphics.hpp"

struct AtlasRegion {
    float x1, y1, x2, y2;

    AtlasRegion(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

class Atlas {
private:
    std::vector<std::pair<std::string, sf::Image>> images;
    std::unordered_map<std::string, AtlasRegion> regions;
    sf::Texture texture;
    sf::Image atlas;
public:

    explicit Atlas(sf::Vector2i atlas_size);

    void register_texture(const std::string &id, const std::string &image_name);

    void build();
};


#endif //LOGISTICHELL_ATLAS_H
