#include "graph.h"
#include <iostream>
#include <string>

// Function to print the graph's structure (nodes and their children)
template <typename State>
void printGraph(const graphns::Graph<State>& graph) {
    std::cout << "Graph Structure:\n";
    const auto& nodes = graph.GetNodes();
    for (size_t i = 0; i < nodes.size(); ++i) {
        const auto& node = nodes[i];
        std::cout << "Node " << i << " (" << node->GetName() << "):\n";
        std::cout << "  State: " << node->state << "\n";
        std::cout << "  Children: ";
        for (const auto& child_weak : node->GetChildren()) {
            if (auto child = child_weak.lock()) {
                std::cout << child->GetName() << " ";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    // Create a graph with int as the State type
    graphns::Graph<int> graph;

    // Add nodes with names and set their states
    auto nodeA = graph.AddNode("A");
    nodeA->state = 100; // Set state for node A
    auto nodeB = graph.AddNode("B");
    nodeB->state = 200;
    auto nodeC = graph.AddNode("C");
    nodeC->state = 300;
    auto nodeD = graph.AddNode("D");
    nodeD->state = 400;

    // Create directed edges
    nodeA->AddChild(nodeB); // A -> B
    nodeA->AddChild(nodeC); // A -> C
    nodeB->AddChild(nodeC); // B -> C
    nodeC->AddChild(nodeD); // C -> D

    // Demonstrate adjacency checks using HasEdge
    std::cout << "Edge from A to B (index 0 to 1): " << graph.HasEdge(0, 1) << "\n";
    std::cout << "Edge from B to A (index 1 to 0): " << graph.HasEdge(1, 0) << "\n";
    std::cout << "Edge from C to D (index 2 to 3): " << graph.HasEdge(2, 3) << "\n";

    // Access nodes by index and name
    std::cout << "\nAccessing nodes:\n";
    std::cout << "Node at index 0: " << graph[0]->GetName() << ", State: " << graph[0]->state << "\n";
    std::cout << "Node named 'C': " << graph["C"]->GetName() << ", State: " << graph["C"]->state << "\n";

    // Print the full graph structure
    std::cout << "\n";
    printGraph(graph);

    // Demonstrate handling of expired weak_ptrs
    {
        auto tempNode = graph.AddNode("Temp");
        nodeD->AddChild(tempNode);
        std::cout << "\nAdded Temp node as child of D\n";
        // tempNode goes out of scope, weak_ptr in D's children becomes expired
    }
    std::cout << "After Temp node goes out of scope:\n";
    printGraph(graph); // Temp won't appear in D's children

    return 0;
}