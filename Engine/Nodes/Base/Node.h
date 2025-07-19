//
// Created by EgorRychkov on 12.04.2025.
//
#include "SFML/Graphics.hpp"
#include "../../EngineContext.h"
#include <memory>

#ifndef LOGISTICHELL_NODE_H
#define LOGISTICHELL_NODE_H


class Node : public std::enable_shared_from_this<Node> {
public:

    static std::shared_ptr<Node>
    create(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0);

    virtual ~Node() = default;

    explicit Node(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0);


    virtual void render(EngineContext &ctx, sf::RenderStates &states);

    virtual void update(EngineContext &ctx);


    void set_render_flag(bool flag);

    void set_update_flag(bool flag);


    void set_priority_relativity(bool is_priority_relative);

    bool get_priority_dependency() const;

    int get_render_priority() const;

    void set_render_priority(int new_render_priority);


    bool get_render_flag() const;

    bool get_update_flag() const;


    [[nodiscard]] virtual int get_node_type() const;

    static std::string get_node_type_str(std::shared_ptr<Node> node);


    virtual sf::Transformable &get_transformable();

    void set_position(const sf::Vector2f &position);

    void set_origin(const sf::Vector2f &position);

    void set_scale(float new_scale);

    const sf::Vector2f &get_origin();

    const sf::Vector2f &get_position();

    void set_rotation(float angle);

    float get_rotation();

    void clear_container();

    void add_node(const std::shared_ptr<Node> &new_node);

    void delete_node(const std::shared_ptr<Node> &node);

    std::string &get_node_id();

    int get_container_volume() const;

    std::vector<std::shared_ptr<Node>> &get_container();


    std::weak_ptr<Node> parent;

private:
    int render_priority;
    int container_volume;
    bool priority_as_relative = true;
    bool render_enabled = true;
    bool update_enabled = true;
    std::vector<std::shared_ptr<Node>> container;
protected:
    std::string node_id;
    sf::Transformable transform;
};


#endif //LOGISTICHELL_NODE_H
