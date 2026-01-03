//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_CONTENTPACKSSYSTEM_H
#define LOGISTICHELL_CONTENTPACKSSYSTEM_H


#include <optional>
#include <filesystem>
#include "../../../Engine/Nodes/Base/Node.h"
#include "ContentPack.h"
#include "../../../Engine/json.hpp"

class GameWorld;

enum class BlockType : uint8_t;

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
    namespace Load {
        void require_condition(bool condition, const std::string &message);

        const nlohmann::json &get_json_field(const nlohmann::json &root, const char *field);

        int get_json_int(const nlohmann::json &root, const char *field);

        float get_json_float(const nlohmann::json &root, const char *field);

        std::string get_json_string(const nlohmann::json &root, const char *field);

        template<typename T, size_t N>
        std::array<T, N> get_json_array(const nlohmann::json &root, const char *field) {
            const auto &array = root.at(field);
            require_condition(array.is_array(), "'" + std::string(field) + "' must be an array.");
            require_condition(array.size() == N,
                              "array at '" + std::string(field) + "' must have size " + std::to_string(N) + ".");
            std::array<T, N> out{};
            for (size_t i = 0; i < N; i++) {
                require_condition(array[i].is_number(),
                                  "array at '" + std::string(field) + "', element at index " + std::to_string(i) +
                                  " must be a number.");
                out[i] = array[i].get<T>();
            }
            return out;
        }

        namespace Unit {
            const std::vector<std::string> available_block_types = {"BusyAttachable", "BusyLocked", "Empty"};

            bool validate_block_type(const std::string &type);

            BlockType parse_block_type(const std::string &type);

            bool validate_block_position(const std::string &key);

            std::pair<int, int> parse_block_position(const std::string &key);
        }
    }

}


class ContentPacksSystem : public Node {
private:
    std::unordered_map<unsigned int, std::shared_ptr<ContentPacks::ContentPack>> content_packs;
    std::unordered_map<std::string, unsigned int> packs_indexer;
    unsigned int max_content_pack_id{};
    std::weak_ptr<GameWorld> world;

    void register_namespace(const std::string &pack_name);

    ContentPacks::DependenciesResolutionResult resolve_dependencies();

    void link_pack_data(const std::shared_ptr<ContentPacks::ContentPack> &pack);

    void load_unit(const std::string &pack_name, const std::filesystem::path &unit);

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

    void load_content_packs(EngineContext &ctx);
};


#endif //LOGISTICHELL_CONTENTPACKSSYSTEM_H
