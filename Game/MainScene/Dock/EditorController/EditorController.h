//
// Created by EgorRychkov on 14.05.2025.
//

#ifndef LOGISTICHELL_EDITORCONTROLLER_H
#define LOGISTICHELL_EDITORCONTROLLER_H

#include "memory"
#include "../BuildingGrid/BuildingGrid.h"
#include "../../Blueprints/BlueprintLoader.h"
#include "../Builder/Builder.h"
#include "DockController.h"

class Dock;

enum class EditorMode : int {
    Attachment,
    Destroying
};

class EditorController {
public:
    static std::shared_ptr<EditorController>
    create(EngineContext &ctx, std::shared_ptr<Dock> dock,
           std::shared_ptr<BuildingGrid> building_grid,
           std::shared_ptr<BlueprintLoader> blueprint_loader);

    explicit EditorController(EngineContext &ctx, std::shared_ptr<Dock> dock,
                              std::shared_ptr<BuildingGrid> building_grid,
                              std::shared_ptr<BlueprintLoader> blueprint_loader);

    void on_mouse_release(sf::Event &event, EngineContext &ctx);

    void on_mouse_moved(sf::Event &event, EngineContext &ctx);

    void on_mouse_exit(EngineContext &ctx);

    void on_mouse_enter(EngineContext &ctx);

    void on_key_release(sf::Event &event, EngineContext &ctx);

    void set_mode(const EditorMode &new_mode, EngineContext &ctx);

    std::shared_ptr<Builder> builder;
    std::weak_ptr<Dock> dock;
private:
    EditorMode editor_mode;

    sf::Vector2i get_grid_cell_position(EngineContext &ctx);
};


#endif //LOGISTICHELL_EDITORCONTROLLER_H
