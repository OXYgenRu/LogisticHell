cmake_minimum_required(VERSION 3.24)
project(LogisticHell)


set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/EgorRychkov/Desktop/SFML-2.6.1/lib/cmake/SFML")
#set(Eigen3_DIR "C:/Users/EgorRychkov/Desktop/libraris/eigen-3.4.0/eigen-3.4.0/cmake")
#set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

#find_package (Eigen3 3.4.0 REQUIRED NO_MODULE)
find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system )

add_executable(LogisticHell main.cpp Engine/Application.h Engine/Application.cpp Engine/EngineContext.h Engine/Nodes/Base/Node.h Engine/Nodes/Base/ContainerNode.h Engine/Nodes/Base/ContainerNode.cpp Engine/Nodes/Base/Node.cpp Engine/Systems/Tree.h Engine/Systems/Tree.cpp Engine/Scene.h Engine/Scene.cpp Engine/Nodes/Base/ContentNode.h Engine/Nodes/Base/ContentNode.cpp Engine/Systems/SceneSystem.h Engine/Systems/SceneSystem.cpp Engine/Nodes/Render/Shapes/Polygon.h Engine/Nodes/Render/Shapes/Polygon.cpp Engine/Nodes/Control/Controller.h Engine/Nodes/Control/Controller.cpp)

target_link_libraries(LogisticHell sfml-graphics sfml-window sfml-system)
#target_link_libraries (Boxel Eigen3::Eigen)
