//
// Created by EgorRychkov on 14.12.2025.
//

#include "ContentPacksSystem.h"
#include "../World/GameWorld.h"

std::shared_ptr<ContentPacksSystem>
ContentPacksSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                           const std::string &node_id,
                           int render_priority) {
    auto node = std::make_shared<ContentPacksSystem>(parent, node_id, render_priority);
    ContentPacksSystem::setup(node, world);
    parent->add_node(node);
    return node;
}


void
ContentPacksSystem::setup(const std::shared_ptr<ContentPacksSystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

std::optional<unsigned int> ContentPacksSystem::get_pack_id(const std::string &pack_name) const {
    auto it = packs_indexer.find(pack_name);
    if (it == packs_indexer.end()) {
        return std::nullopt;
    }
    return it->second;
}

void ContentPacksSystem::update(EngineContext &ctx) {

}

void ContentPacksSystem::on_world_open() {
    ContentPacks::DependenciesResolutionResult result = resolve_dependencies();
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::Success) {
        std::cout << "Packs successfully loaded:\n";
        for (auto &to: result.get_loading_order()) {
            content_packs[to]->on_world_open(*world.lock()->get_api());
            std::cout << content_packs[to]->get_pack_name() << '\n';
        }

        return;
    }
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::PackNotFound) {
        for (auto &to: result.get_missed_packs()) {
            std::cerr << to.first << " requirements error: " << to.second << " not found\n";
        }
        throw std::runtime_error("ContentPacksSystem: pack not found");
    }
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::CircularDependencies) {
        std::cerr << "Cycle dependencies: ";
        for (auto &to: result.get_cycle()) {
            std::cerr << to << " -> ";
        }
        std::cerr << result.get_cycle()[0] << '\n';
        throw std::runtime_error("ContentPacksSystem: cycle dependencies");
    }
}

void ContentPacksSystem::register_namespace(const std::string &pack_name) {
    world.lock()->get_values_global_storage()->create_namespace(pack_name);
}

enum class VertexStatus : int8_t {
    Unused,
    In_progress,
    Done

};

static bool has_cycle(unsigned int v,
                      std::unordered_map<unsigned int, VertexStatus> &used,
                      std::unordered_map<unsigned int, std::vector<unsigned int>> &graph,
                      std::vector<unsigned int> &order,
                      std::unordered_map<unsigned int, unsigned int> &parent,
                      unsigned int &cycle_start,
                      unsigned int &cycle_end) {
    used[v] = VertexStatus::In_progress;
    for (auto &to: graph[v]) {
        if (used[to] == VertexStatus::Unused) {
            parent[to] = v;
            if (has_cycle(to, used, graph, order, parent, cycle_start, cycle_end)) {
                return true;
            }
        } else if (used[to] == VertexStatus::In_progress) {
            cycle_start = v;
            cycle_end = to;
            return true;
        }
    }
    used[v] = VertexStatus::Done;
    order.push_back(v);
    return false;
}

ContentPacks::DependenciesResolutionResult ContentPacksSystem::resolve_dependencies() {
    ContentPacks::DependenciesResolutionStatus state = ContentPacks::DependenciesResolutionStatus::Success;
    std::vector<std::pair<std::string, std::string>> missed_packs;
    std::unordered_map<unsigned int, std::vector<unsigned int>> graph;


    for (auto &to: this->content_packs) {
        graph[to.first];
        for (const ContentPacks::Dependence &current: to.second->get_dependencies()) {
            if (!this->get_pack_id(current.get_pack()).has_value()) {
                state = ContentPacks::DependenciesResolutionStatus::PackNotFound;
                missed_packs.emplace_back(to.second->get_pack_name(), current.get_pack());
                continue;
            }
            if(current.get_type() == ContentPacks::DependenceType::Presence){
                continue;
            }
            unsigned int pack_id = this->get_pack_id(current.get_pack()).value();
            graph[pack_id].emplace_back(to.first);
        }
    }
    if (state == ContentPacks::DependenciesResolutionStatus::PackNotFound) {
        return {state, {}, missed_packs, {}};
    }

    std::unordered_map<unsigned int, VertexStatus> used;
    std::vector<unsigned int> order;
    std::unordered_map<unsigned int, unsigned int> parent;
    std::vector<std::string> cycle;
    unsigned int cycle_start, cycle_end;

    for (auto &to: graph) {
        used[to.first] = VertexStatus::Unused;
    }

    for (auto &to: graph) {
        if (used[to.first] != VertexStatus::Unused) {
            continue;
        }
        if (has_cycle(to.first, used, graph, order, parent, cycle_start, cycle_end)) {
            for (unsigned int v = cycle_start; v != cycle_end; v = parent[v]) {
                cycle.push_back(content_packs[v]->get_pack_name());
            }
            cycle.push_back(content_packs[cycle_end]->get_pack_name());
            std::reverse(cycle.begin(), cycle.end());
            return {ContentPacks::DependenciesResolutionStatus::CircularDependencies,
                    cycle,
                    {},
                    {}};
        }
    }
    std::reverse(order.begin(), order.end());
    return {ContentPacks::DependenciesResolutionStatus::Success,
            {},
            {},
            order};
}