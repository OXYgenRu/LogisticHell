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

add_executable(LogisticHell main.cpp Engine/Application.h Engine/Application.cpp Engine/EngineContext.h Engine/Nodes/Base/Node.h Engine/Nodes/Base/ContainerNode.h Engine/Nodes/Base/ContainerNode.cpp Engine/Nodes/Base/Node.cpp Engine/Systems/Tree.h Engine/Systems/Tree.cpp Engine/Scene.h Engine/Scene.cpp Engine/Nodes/Base/ContentNode.h Engine/Nodes/Base/ContentNode.cpp Engine/Systems/SceneSystem.h Engine/Systems/SceneSystem.cpp Engine/Nodes/Render/Shapes/Polygon.h Engine/Nodes/Render/Shapes/Polygon.cpp Engine/Systems/ControlSystem.h Engine/Systems/ControlSystem.cpp Engine/Nodes/Control/Controller.cpp Engine/Nodes/Base/CameraNode.h Engine/Nodes/Base/CameraNode.cpp Engine/Nodes/Control/CameraController.h Engine/Nodes/Control/CameraController.cpp Engine/Nodes/Render/Shapes/Text.h Engine/Nodes/Render/Shapes/Text.cpp Engine/Nodes/UI/UICollider.h Engine/Nodes/UI/UICollider.cpp Engine/Systems/UICollidersSystem.h Engine/Systems/UICollidersSystem.cpp Engine/Tools.h Game/Tests/UITest/UIScene.h Game/Tests/UITest/UIScene.cpp Game/Tests/UITest/TestCollider.h Game/Tests/UITest/TestCollider.cpp Engine/Nodes/Render/Sprites/Sprite.h Engine/Nodes/Render/Sprites/Sprite.cpp Engine/Nodes/Physics/World.h Engine/Nodes/Physics/World.cpp Game/Tests/Physics/PhysicsScene.h Game/Tests/Physics/PhysicsScene.cpp Game/Tests/Physics/BoxExample.h Game/Tests/Physics/BoxExample.cpp Engine/Nodes/Physics/RigidBody.h Engine/Nodes/Physics/RigidBody.cpp Engine/Nodes/Physics/CollisionPolygon.h Engine/Nodes/Physics/CollisionPolygon.cpp Game/Tests/PhysicsNodes/TestBox.h Game/Tests/PhysicsNodes/TestBox.cpp Game/Tests/PhysicsNodes/PhysicsTestScene.h Game/Tests/PhysicsNodes/PhysicsTestScene.cpp Game/MainScene/MainScene.h Game/MainScene/MainScene.cpp Game/Tests/PhysicsNodes/TestController.h Game/Tests/PhysicsNodes/TestController.cpp Engine/Nodes/Render/Shapes/TexturedQuad.h Engine/Nodes/Render/Shapes/TexturedQuad.cpp Game/MainScene/Structure/Block/BaseBlock.h Game/MainScene/Structure/Block/BaseBlock.cpp Game/MainScene/Structure/Grid/Grid.h Game/MainScene/Structure/Grid/Grid.cpp Game/MainScene/Structure/Grid/GridViewer.h Game/MainScene/Structure/Grid/GridViewer.cpp Game/MainScene/Structure/Structure.h Game/MainScene/Structure/Structure.cpp)

target_link_libraries(LogisticHell sfml-graphics sfml-window sfml-system box2d)

#target_link_libraries (Boxel Eigen3::Eigen)
