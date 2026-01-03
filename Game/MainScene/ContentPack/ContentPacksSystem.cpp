//
// Created by EgorRychkov on 14.12.2025.
//

#include <regex>
#include <filesystem>
#include <fstream>
#include "ContentPacksSystem.h"
#include "../World/GameWorld.h"
#include "../../../Engine/Application.h"

constexpr std::string_view PACKS_FOLDER = "content_packs";
constexpr std::string_view UNITS_FOLDER = "units";
constexpr std::string_view UNIT_EXTENSION = ".json";

using namespace ContentPacks;

void Load::require_condition(bool condition, const std::string &message) {
    if (condition) {
        return;
    }
    throw std::runtime_error("[ContentPacks::Load]::require_condition: " + message);
}

const nlohmann::json &ContentPacks::Load::get_json_field(const nlohmann::json &root, const char *field) {
    if (!root.contains(field)) {
        throw std::runtime_error("[ContentPacks::Load]::get_json_field: field '" + std::string(field) + "' is missed.");
    }
    return root.at(field);
}

int ContentPacks::Load::get_json_int(const nlohmann::json &root, const char *field) {
    nlohmann::json element = get_json_field(root, field);
    require_condition(element.is_number_integer(),
                      "[ContentPacks::Load]::get_json_int: field '" + std::string(field) + "' is not int.");
    return element.get<int>();
}

float ContentPacks::Load::get_json_float(const nlohmann::json &root, const char *field) {
    nlohmann::json element = get_json_field(root, field);
    require_condition(element.is_number_float(),
                      "[ContentPacks::Load]::get_json_float: field '" + std::string(field) + "' is not float.");
    return element.get<float>();
}

std::string ContentPacks::Load::get_json_string(const nlohmann::json &root, const char *field) {
    nlohmann::json element = get_json_field(root, field);
    require_condition(element.is_string(),
                      "[ContentPacks::Load]::get_json_string: field '" + std::string(field) + "' is not string.");
    return element.get<std::string>();
}

bool Load::Unit::validate_block_type(const std::string &type) {
    for (const std::string &type_: Load::Unit::available_block_types) {
        if (type_ == type) {
            return true;
        }
    }
    return false;
}

BlockType parse_block_type(const std::string &type) {
    if (type == "BusyAttachable") {
        return BlockType::BusyAttachable;
    }
    if (type == "BusyLocked") {
        return BlockType::BusyLocked;
    }
    if (type == "Empty") {
        return BlockType::Empty;
    }
    return BlockType::Empty;
}

bool ContentPacks::Load::Unit::validate_block_position(const std::string &key) {
    static const std::regex re(R"(^\d+_\d+$)");
    return std::regex_match(key, re);
}

std::pair<int, int> Load::Unit::parse_block_position(const std::string &key) {
    auto pos = key.find('_');
    int x = std::stoi(key.substr(0, pos));
    int y = std::stoi(key.substr(pos + 1));
    return {x, y};
}

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

static bool is_pack_name_correct(const std::string &pack_name) {
    static const std::regex re(R"(^[A-Za-z_][A-Za-z_]*$)");
    return std::regex_match(pack_name, re);
}


void ContentPacksSystem::load_content_packs(EngineContext &ctx) {
    for (auto &to: this->content_packs) {
        if (!is_pack_name_correct(to.second->get_pack_name())) {
            std::cerr << "[ContentPacksSystem]: pack name is incorrect: " << to.second->get_pack_name() << std::endl;
            exit(0);
        }
    }
    ContentPacks::DependenciesResolutionResult result = resolve_dependencies();
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::Success) {
        std::cout << "[ContentPacksSystem]: " << "Dependencies successfully resolved, loading packs:" << std::endl;
        for (auto &to: result.get_loading_order()) {
            try {
                link_pack_data(content_packs[to]);
            }
            catch (const std::exception &e) {
                std::string error =
                        "[ContentPacksSystem::load_content_packs]:link_pack_data: error during loading pack '" +
                        content_packs[to]->get_pack_name() + "'\n";
                error += e.what();
                throw std::runtime_error(error);
            }
            content_packs[to]->on_world_open(*world.lock()->get_api());
            std::cout << "Loaded: '" << content_packs[to]->get_pack_name() << "'" << std::endl;
        }
        std::cout << "[ContentPacksSystem]: " << "Packs successfully loaded" << std::endl;
        ctx.app->texture_atlas->build();
        return;
    }
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::PackNotFound) {
        for (auto &to: result.get_missed_packs()) {
            std::cerr << "[ContentPacksSystem]: " << to.first
                      << " requirements error: " << to.second << " not found\n";
        }
        throw std::runtime_error("ContentPacksSystem: pack not found");
    }
    if (result.get_status() == ContentPacks::DependenciesResolutionStatus::CircularDependencies) {
        std::cerr << "[ContentPacksSystem]: " << "Cycle dependencies: ";
        for (auto &to: result.get_cycle()) {
            std::cerr << to << " -> ";
        }
        std::cerr << result.get_cycle()[0] << '\n';
        throw std::runtime_error("[ContentPacksSystem]: cycle dependencies");
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
            if (current.get_type() == ContentPacks::DependenceType::Presence) {
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

void ContentPacksSystem::link_pack_data(const std::shared_ptr<ContentPacks::ContentPack> &pack) {
    if (!std::filesystem::exists(PACKS_FOLDER)) {
        throw std::runtime_error("[ContentPacksSystem::link_pack_data]::filesystem: content packs folder not found");
    }
    std::filesystem::path pack_folder = std::filesystem::path(PACKS_FOLDER) / pack->get_pack_name();
    if (!std::filesystem::exists(pack_folder)) {
        throw std::runtime_error(
                "[ContentPacksSystem::link_pack_data]::filesystem: folder of pack '" + pack->get_pack_name() +
                "' not found");
    }
    std::filesystem::path units_folder = pack_folder / UNITS_FOLDER;
    if (!std::filesystem::exists(units_folder)) {
        throw std::runtime_error(
                "[ContentPacksSystem::link_pack_data]::filesystem: units folder of pack '" + pack->get_pack_name() +
                "' not found");
    }
    for (const auto &unit: std::filesystem::directory_iterator(units_folder)) {
        if (!unit.is_regular_file()) {
            std::cout
                    << "[ContentPacksSystem]: Warning, foreign folder in units folder: " +
                       unit.path().string()
                    << std::endl;
            continue;
        }
        if (unit.path().extension() != UNIT_EXTENSION) {
            std::cout
                    << "[ContentPacksSystem]: Warning, foreign file in units folder: " +
                       unit.path().string()
                    << std::endl;
            continue;
        }
        try {
            load_unit(pack->get_pack_name(), unit);
        }
        catch (const std::exception &e) {
            std::string error =
                    "[ContentPacksSystem::link_pack_data]::load_unit: error during loading unit '" +
                    unit.path().filename().string() + "'\n";
            error += e.what();
            throw std::runtime_error(error);
        }
    }
}


void ContentPacksSystem::load_unit(const std::string &pack_name, const std::filesystem::path &unit) {
    std::ifstream file(unit.string());
    if (!file) {
        throw std::runtime_error(
                "[ContentPacksSystem::load_unit]:filesystem: can not to open json file: " + unit.string());
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    nlohmann::json out;
    try {
        out = nlohmann::json::parse(buffer.str());
    }
    catch (const nlohmann::json::exception &e) {
        std::string error = e.what();
        throw std::runtime_error(
                "[ContentPacksSystem::load_unit]:json: error during parse file: " + unit.string() + " error\n" + error);
    }


    std::string unit_name = pack_name + ":" + unit.stem().string();

    const auto &grid = ContentPacks::Load::get_json_field(out, "grid");
    Load::require_condition(grid.is_array() && grid.size() == 2, "grid must be array of size 2.");
    Load::require_condition(grid[0].is_number_integer() && grid[1].is_number_integer(),
                            "grid must contains integers.");

    int grid_x = grid[0].get<int>();
    int grid_y = grid[1].get<int>();

    Blueprint unit_blueprint({grid_x, grid_y}, 0);

    Load::require_condition(grid_x > 0 && grid_y > 0, "grid values must be > 0");

    const auto &components = Load::get_json_field(out, "components");
    Load::require_condition(components.is_array(), "components must be array.");

    for (size_t i = 0; i < components.size(); i++) {
        const auto &component = components[i];
        Load::require_condition(component.is_object(),
                                "component at index '" + std::to_string(i) + "' must be an object.");
        Load::require_condition(Load::get_json_field(component, "body_type").is_string(),
                                "in component at index '" + std::to_string(i) +
                                "' field 'body_type' is not a string.");
        unit_blueprint.add_component();


        const auto &blocks = component.at("blocks");
        Load::require_condition(blocks.is_object(),
                                "in component at index '" + std::to_string(i) +
                                "' field 'blocks' is not an object.");

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            const std::string &key = it.key();
            Load::require_condition(Load::Unit::validate_block_position(key),
                                    "block key must be like 'x_y', got: '" + key + "'.");

            auto [x, y] = Load::Unit::parse_block_position(key);
            Load::require_condition(x >= 0 and x < grid_x and y >= 0 and y < grid_y,
                                    "block position out of grid: '" + key + "'");

            const auto &block = it.value();
            Load::require_condition(block.is_object(), "block at '" + key + "' is not an object.");

            Load::require_condition(Load::get_json_field(block, "type").is_string(),
                                    "in block at '" + key + "' field type is not a string.");
            Load::require_condition(Load::get_json_field(block, "density").is_number(),
                                    "in block at '" + key + "' field density is not a float.");
            Load::require_condition(Load::get_json_field(block, "friction").is_number(),
                                    "in block at '" + key + "' field friction is not a float.");
            std::string string_type = Load::get_json_field(block, "type").get<std::string>();
            float density = Load::get_json_field(block, "density").get<float>();
            float friction = Load::get_json_field(block, "friction").get<float>();

            Load::require_condition(Load::Unit::validate_block_type(string_type),
                                    "in block at '" + key + "' field type is match to available types: '" +
                                    string_type + "'.");


            unit_blueprint.components[i]->set_block({x, y},
                                                    BlueprintBlock(parse_block_type(string_type),
                                                                   density,
                                                                   friction));
        }
    }

    const auto &render_features = Load::get_json_field(out, "render_features");
    Load::require_condition(render_features.is_object(), "'render_features' must be an object.");

    std::shared_ptr<UnitProperties> unit_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);

    for (auto it = render_features.begin(); it != render_features.end(); ++it) {
        const std::string &key = it.key();

        const auto &feature = it.value();
        Load::require_condition(feature.is_object(), "render feature at '" + key +
                                                     "' must be an object.");
        Load::require_condition(Load::get_json_field(feature, "texture").is_string(),
                                "in render feature at '" + key + "' texture must be a string");
        std::string texture = Load::get_json_field(feature, "texture").get<std::string>();

        std::array<int, 2> anchor = Load::get_json_array<int, 2>(feature, "anchor");

        Load::require_condition(Load::get_json_field(feature, "render_priority").is_number_integer(),
                                "in render feature at '" + key + "' render_priority must be a int");
        int render_priority = Load::get_json_field(feature, "render_priority").get<int>();

        std::array<float, 2> position = Load::get_json_array<float, 2>(feature, "position");

        std::array<float, 2> size = Load::get_json_array<float, 2>(feature, "size");

        Load::require_condition(Load::get_json_field(feature, "angle").is_number_integer(),
                                "in render feature at '" + key + "' angle must be a int");
        float angle = Load::get_json_field(feature, "angle").get<float>();

        unit_properties->add_render_feature(
                UnitRenderFeature(key, texture, {anchor[0], anchor[1]}, render_priority, {position[0], position[1]},
                                  {size[0], size[1]}, angle));
    }
    if (!out.contains("revolute_joints")) {
        return;
    }
    const auto &revolute_joints = Load::get_json_field(out, "revolute_joints");
    Load::require_condition(revolute_joints.is_object(), "revolute_joints must be an object.");

    for (auto it = revolute_joints.begin(); it != revolute_joints.end(); ++it) {
        const std::string &joint_name = it.key();
        const auto &joint = it.value();
        Load::require_condition(joint.is_object(), "revolute joint at '" + joint_name + "' must be an object.");

        auto block_position = Load::get_json_array<int, 2>(joint, "block_position");
        auto component_block_a = Load::get_json_array<int, 2>(joint, "component_block_a");
        auto component_block_b = Load::get_json_array<int, 2>(joint, "component_block_b");

        Load::require_condition(block_position[0] >= 0 and block_position[0] < grid_x and block_position[1] >= 0 and
                                block_position[1] < grid_y,
                                "revolute joint at '" + joint_name + "' has incorrect block position");
        Load::require_condition(
                component_block_a[0] >= 0 and component_block_a[0] < grid_x and component_block_a[1] >= 0 and
                component_block_a[1] < grid_y,
                "revolute joint at '" + joint_name + "' has incorrect component_block_a position");
        Load::require_condition(
                component_block_b[0] >= 0 and component_block_b[0] < grid_x and component_block_b[1] >= 0 and
                component_block_b[1] < grid_y,
                "revolute joint at '" + joint_name + "' has incorrect component_block_b position");
        unit_properties->add_revolute_joint(
                BlueprintJoints::RevoluteJoint(joint_name,
                                               {block_position[0], block_position[1]},
                                               {component_block_a[0], component_block_a[1]},
                                               {component_block_b[0], component_block_b[1]}));
    }
    world.lock()->get_blueprints_loader()->register_unit(unit_name, unit_blueprint, unit_properties, nullptr);
}