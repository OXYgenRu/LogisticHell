//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_CONTENTPACKSSYSTEM_H
#define LOGISTICHELL_CONTENTPACKSSYSTEM_H


#include <optional>
#include "../../../Engine/Nodes/Base/Node.h"
#include "ContentPack.h"

class GameWorld;

namespace ContentPacks {
    enum class DependenciesResolutionStatus {
        CircularDependencies,
        PackNotFound,
        Success,
    };

    class DependenciesResolutionResult {
    private:
        DependenciesResolutionStatus status;
        std::vector<std::string> cycle;
        std::vector<std::pair<std::string, std::string>> missed_packs;
        std::vector<unsigned int> loading_order;
    public:
        DependenciesResolutionResult(DependenciesResolutionStatus info,
                                     std::vector<std::string> cycle,
                                     std::vector<std::pair<std::string, std::string>> missed_packs,
                                     std::vector<unsigned int> loading_order) :
                status(info),
                cycle(std::move(cycle)),
                missed_packs(std::move(missed_packs)),
                loading_order(std::move(loading_order)) {}

        const DependenciesResolutionStatus &get_status() {
            return status;
        }

        const std::vector<std::string> &get_cycle() {
            return cycle;
        }

        const std::vector<std::pair<std::string, std::string>> &get_missed_packs() {
            return missed_packs;
        }

        const std::vector<unsigned int> &get_loading_order() {
            return loading_order;
        }
    };

}

class ContentPacksSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<ContentPacks::ContentPack>> content_packs;
    std::unordered_map<std::string, unsigned int> packs_indexer;
    unsigned int max_content_pack_id{};
    std::weak_ptr<GameWorld> world;

    void register_namespace(const std::string &pack_name);

    ContentPacks::DependenciesResolutionResult resolve_dependencies();

public:
    static std::shared_ptr<ContentPacksSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit ContentPacksSystem(const std::shared_ptr<Node> &parent, const std::string &node_id,
                                int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {};

    static void setup(const std::shared_ptr<ContentPacksSystem> &node, const std::shared_ptr<GameWorld> &world);

    template<typename T>
    std::shared_ptr<ContentPacks::ContentPack> register_content_pack(const std::string &pack_name) {
        unsigned int pack_id = max_content_pack_id++;
        content_packs[pack_id] = std::make_shared<T>(pack_name, pack_id);
        packs_indexer[pack_name] = pack_id;
        register_namespace(pack_name);
        return content_packs[pack_id];
    }

    std::optional<unsigned int> get_pack_id(const std::string &pack_name) const;

    void update(EngineContext &ctx) override;

    void on_world_open();
};


#endif //LOGISTICHELL_CONTENTPACKSSYSTEM_H
