//
// Created by EgorRychkov on 07.04.2025.
//
#include "iostream"
#include "Engine/Application.h"
#include "Engine/Nodes/Base/Node.h"
#include "Engine/Nodes/Base/ContainerNode.h"
#include "Engine/Nodes/Base/ContentNode.h"
#include "Engine/Scene.h"

void print_tree(const std::shared_ptr<Node> &node, int depth = 0) {
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::cout << (node->is_leaf() ? "Leaf" : "Container") << " Node\n";

    for (const auto &child: node->children) {
        print_tree(child, depth + 1);
    }
}

int main() {
//    Application app(sf::VideoMode(1600, 900), "LogisticHell");
//    app.start();
    auto scene = std::make_shared<Scene>();
//
//    auto node1 = std::make_shared<ContentNode>(scene);
//    auto node2 = std::make_shared<ContentNode>(scene);
//
//    auto node1_1 = std::make_shared<ContainerNode>(scene);
//
//    auto node_1_2 = std::make_shared<ContentNode>(node1_1);
//    auto node_1_3 = std::make_shared<ContentNode>(node1_1);
//    for (auto to: node1_1->children) {
//        std::cout << to->is_leaf() << '\n';
//    }
    auto node1 = ContentNode::create(scene);
    auto node2 = ContentNode::create(scene);
    auto node1_1 = ContainerNode::create(scene);
    auto node1_2 = ContentNode::create(node1_1);
    auto node1_3 = ContentNode::create(node1_1);
    print_tree(scene);
    return 0;
}