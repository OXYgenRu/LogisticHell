cmake_minimum_required(VERSION 3.24)
project(LogisticHell)


set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/EgorRychkov/Desktop/SFML-2.6.1/lib/cmake/SFML")

set(BOX2D_ROOT "C:/Users/EgorRychkov/CLionProjects/box2d/install")

include_directories(C:/Users/EgorRychkov/CLionProjects/box2d/install/include)

link_directories(C:/Users/EgorRychkov/CLionProjects/box2d/install/lib)
#set(Eigen3_DIR "C:/Users/EgorRychkov/Desktop/libraris/eigen-3.4.0/eigen-3.4.0/cmake")
#set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

#find_package (Eigen3 3.4.0 REQUIRED NO_MODULE)


find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system)

add_executable(LogisticHell main.cpp Engine/Application.h Engine/Application.cpp Engine/EngineContext.h Engine/Nodes/Base/Node.h Engine/Nodes/Base/Node.cpp Engine/Systems/Tree.h Engine/Systems/Tree.cpp Engine/Scene.h Engine/Scene.cpp Engine/Systems/SceneSystem.h Engine/Systems/SceneSystem.cpp Engine/Nodes/Render/Shapes/Polygon.h Engine/Nodes/Render/Shapes/Polygon.cpp Engine/Systems/ControlSystem.h Engine/Systems/ControlSystem.cpp Engine/Nodes/Control/Controller.cpp Engine/Nodes/Base/CameraNode.h Engine/Nodes/Base/CameraNode.cpp Engine/Nodes/Control/CameraController.h Engine/Nodes/Control/CameraController.cpp Engine/Nodes/Render/Shapes/Text.h Engine/Nodes/Render/Shapes/Text.cpp Engine/Nodes/UI/Collider.h Engine/Nodes/UI/Collider.cpp Engine/Systems/UICollidersSystem.h Engine/Systems/UICollidersSystem.cpp Engine/Tools.h Game/Tests/UITest/UIScene.h Game/Tests/UITest/UIScene.cpp Game/Tests/UITest/TestCollider.h Game/Tests/UITest/TestCollider.cpp Engine/Nodes/Render/Sprites/Sprite.h Engine/Nodes/Render/Sprites/Sprite.cpp Engine/Nodes/Physics/World.h Engine/Nodes/Physics/World.cpp  Engine/Nodes/Physics/RigidBody.h Engine/Nodes/Physics/RigidBody.cpp Engine/Nodes/Physics/CollisionPolygon.h Engine/Nodes/Physics/CollisionPolygon.cpp   Game/MainScene/MainScene.h Game/MainScene/MainScene.cpp  Engine/Nodes/Render/Shapes/TexturedQuad.h Engine/Nodes/Render/Shapes/TexturedQuad.cpp  Game/MainScene/Dock/Dock.h Game/MainScene/Dock/Dock.cpp Game/MainScene/Dock/EditorInterface/EditorInterface.h Game/MainScene/Dock/EditorInterface/EditorInterface.cpp Game/MainScene/Dock/EditorController/DockController.h Game/MainScene/Dock/EditorController/DockController.cpp Game/MainScene/Dock/EditorController/DockController.h Game/MainScene/Dock/EditorController/DockController.h    Game/MainScene/Blueprints/Blueprint/Blueprint.h Game/MainScene/Blueprints/Blueprint/Blueprint.cpp Game/MainScene/Blueprints/BlueprintComponent/BlueprintComponent.h Game/MainScene/Blueprints/BlueprintComponent/BlueprintComponent.cpp Game/MainScene/Dock/Builder/Builder.h Game/MainScene/Dock/Builder/Builder.cpp Engine/Systems/Atlas.h Engine/Systems/Atlas.cpp  Game/MainScene/Blueprints/BlueprintLoader.h Game/MainScene/Blueprints/BlueprintLoader.cpp Game/MainScene/Dock/EditorController/EditorController.h Game/MainScene/Dock/EditorController/EditorController.cpp Engine/Nodes/UI/UIPolygon.h Engine/Nodes/UI/UIPolygon.cpp Engine/Nodes/UI/Anchor.h Engine/Nodes/UI/Button.h Engine/Nodes/UI/Button.cpp Engine/Nodes/UI/Rectangle.h Engine/Nodes/UI/Rectangle.cpp Engine/Nodes/UI/VerticalList.h Engine/Nodes/UI/VerticalList.cpp Game/MainScene/Dock/EditorInterface/BlocksInventory.h Game/MainScene/Dock/EditorInterface/BlocksInventory.cpp Game/MainScene/Blueprints/UnitProperties/UnitProperties.h Game/MainScene/Blueprints/UnitProperties/UnitProperties.cpp Game/MainScene/Blueprints/Blueprint/Utils.h  Game/MainScene/Structure/Component.h Game/MainScene/Structure/Component.h Game/MainScene/Structure/Component.cpp Game/MainScene/Blueprints/UnitProperties/UnitRenderFeature.h Game/MainScene/Blueprints/UnitProperties/UnitRenderFeature.cpp Game/MainScene/Dock/Builder/BuildingGrid.h Game/MainScene/Dock/Builder/BuildingGrid.cpp)

target_link_libraries(LogisticHell sfml-graphics sfml-window sfml-system box2d)

#target_link_libraries (Boxel Eigen3::Eigen)
