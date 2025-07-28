//
// Created by EgorRychkov on 14.05.2025.
//

#ifndef LOGISTICHELL_EDITORCONTROLLER_H
#define LOGISTICHELL_EDITORCONTROLLER_H

#include "memory"
#include "../Builder/BuildingGrid.h"
#include "../Builder/Builder.h"
#include "DockController.h"
#include "../EditorInterface/EditorInterface.h"

class Dock;

enum class EditorMode : int {
    Attachment,
    Destroying
};

class EditorController {
public:
    static std::shared_ptr<EditorController>
    create(EngineContext &ctx,  const std::shared_ptr<Dock> &dock,
           const std::shared_ptr<BuildingGrid> &building_grid,
           const std::shared_ptr<GameWorld>& world);

    explicit EditorController(EngineContext &ctx, const std::shared_ptr<Dock> &dock,
                              const std::shared_ptr<BuildingGrid> &building_grid,
                              const std::shared_ptr<GameWorld> &world);

    void on_mouse_release(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position);

    void on_mouse_moved(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position);

    void on_mouse_exit(EngineContext &ctx, const sf::Vector2f &local_position);

    void on_mouse_enter(EngineContext &ctx, const sf::Vector2f &local_position);

    void on_key_release(sf::Event &event, EngineContext &ctx);

    void set_mode(const EditorMode &new_mode, EngineContext &ctx);

    void set_unit(const unsigned int &unit_index, EngineContext &ctx);

    std::shared_ptr<Builder> builder;
    std::shared_ptr<EditorInterface> interface;
    std::weak_ptr<Dock> dock;
private:
    EditorMode editor_mode;
    bool is_preview_active;

    sf::Vector2i get_grid_cell_position(EngineContext &ctx, const sf::Vector2f &local_position);
};


#endif //LOGISTICHELL_EDITORCONTROLLER_H
