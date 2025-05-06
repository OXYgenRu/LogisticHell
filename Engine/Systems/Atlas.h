//
// Created by EgorRychkov on 06.05.2025.
//

#ifndef LOGISTICHELL_ATLAS_H
#define LOGISTICHELL_ATLAS_H

#include "SFML/Graphics.hpp"
#include "memory"

struct AtlasRegion {
    int x1, y1, x2, y2;

    AtlasRegion() = default;

    AtlasRegion(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    std::vector<sf::Vector2f> get_rect() const;
};

class Atlas {
private:
    std::vector<std::pair<std::string, sf::Image>> images;
    std::unordered_map<std::string, AtlasRegion> regions;
    std::unique_ptr<sf::Texture> texture;
    sf::Image atlas;
public:

    explicit Atlas(sf::Vector2i atlas_size);

    void register_texture(const std::string &id, const std::string &image_name);

    void build();

    const AtlasRegion &get_region(const std::string &name) const;

    sf::Texture *get_texture() const;
};


#endif //LOGISTICHELL_ATLAS_H
