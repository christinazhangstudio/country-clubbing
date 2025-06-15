#ifndef GRAPH_H
#define GRAPH_H

// #pragma once    // ensures header file used exactly once by compiler, supposely better than include guards

#include <string>
#include <string_view>
#include <memory>   // provides smart pointers (shared_ptr, weak_ptr)
#include <unordered_set>    // hash based containers
#include <unordered_map>
#include <vector>

// Namespace to avoid name clashes and group related functionality
namespace graphns {

// [[nodiscard]] encourages users not to ignore the return value.
// noexcept reflects that the function doesn’t throw (hashing and weak_ptr::lock are noexcept).

// custom hash function for std::weak_ptr<T> to allow
// std::weak_ptr to be used as a key in hash-based containers
//
// operator() takes a std::weak_ptr<T> and attempts to lock it to obtain a std::shared_ptr<T>
// then hashes the std::shared_ptr<T> using std library hash func for std::shared_ptr
template<typename T>
struct WeakPtrHash {
    // computes the hash of a weak_ptr by locking it to a shared_ptr
    // Returns the hash of the shared_ptr (0 if the weak_ptr is expired)
    [[nodiscard]] size_t operator()(const std::weak_ptr<T>& wp) const noexcept {
        return std::hash<std::shared_ptr<T>>{}(wp.lock());
    }
};

// Equality comparator for std::weak_ptr<T> to enable use in unordered containers
template <typename T>
struct WeakPtrEqual {
    // Compares two weak_ptrs for equality based on shared ownership
    // Returns true if they point to the same object (or both are expired)
    [[nodiscard]] bool operator()(const std::weak_ptr<T>& left,
                                  const std::weak_ptr<T>& right) const noexcept {
        return !left.owner_before(right) && !right.owner_before(left);
    }
};

// Directed graph class template, where nodes hold a user-defined State type
template <typename State>
class Graph {
public:
    // Nested Node class representing a vertex in the graph
    class Node {
    public:
        // Constructs a node with an optional name (defaults to empty)
        // Explicit to prevent implicit conversions from string_view
        explicit Node(std::string_view name = "") : name_(name) {}

        // Checks if 'other' is an adjacent node (i.e., there’s an edge to it)
        // Returns true if 'other' is in the children set
        [[nodiscard]] bool IsAdjacentTo(const std::shared_ptr<Node>& other) const {
            return children_.find(other) != children_.end();
        }

        // Adds a child node, creating a directed edge to it
        // Ignores null pointers for safety
        void AddChild(const std::shared_ptr<Node>& child) {
            if (child) {
                children_.insert(child);
            }
        }

        // Returns the set of adjacent nodes (children) as weak_ptrs
        // Weak_ptrs prevent strong reference cycles in the graph
        [[nodiscard]] const std::unordered_set<std::weak_ptr<Node>,
                                              WeakPtrHash<Node>,
                                              WeakPtrEqual<Node>>& GetChildren() const {
            return children_;
        }

        // Returns the node’s name
        // return a reference to std::string
        // i.e. a const reference to the name_ member of the Node class
        // could also return by value or a pointer, but each have cons (memory overhead / possible null)
        // no string_view because string_view doesn't own string data so only safe if name_ string outlives the view
        // mostly nonidiomatic, can be problematic if Node is destroyed while the view is in use.
        // string_view is used when the string is not owned by the object.
        // Here, name_ is owned, so the reference is more appropriate.
        [[nodiscard]] const std::string& GetName() const noexcept {
            return name_;
        }

        // Public member to store user-defined state data
        // Accessible directly for flexibility
        State state;

    private:
        // Node’s name, stored as a string for persistence
        std::string name_;
        // Set of adjacent nodes (outgoing edges), stored as weak_ptrs
        // Uses custom hash and equality functors for weak_ptr
        std::unordered_set<std::weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> children_;
    };

    // Checks if there’s a directed edge from node i to node j
    // Returns false if i == j or indices are out of bounds
    [[nodiscard]] bool HasEdge(size_t i, size_t j) const {
        if (i == j || i >= nodes_.size() || j >= nodes_.size()) {
            return false;
        }
        return nodes_[i]->IsAdjacentTo(nodes_[j]);
    }

    // Add a new node with an optional name and returns a shared_ptr to it
    // If name is non-empty, stores the node in the named_nodes_ map
    std::shared_ptr<Node> AddNode(std::string_view name = "") {
        auto node = std::make_shared<Node>(name);
        nodes_.push_back(node);
        if (!name.empty()) {
            named_nodes_.emplace(name, node);
        }
        return node;
    }

    // Accesses a node by its index in the nodes vector
    // Throws std::out_of_range if the index is invalid
    [[nodiscard]] const std::shared_ptr<Node>& operator[](size_t i) const {
        return nodes_.at(i);
    }

    // Accesses a node by its name
    // Throws std::out_of_range if the name doesn’t exist
    [[nodiscard]] const std::shared_ptr<Node>& operator[](std::string_view name) const {
        return named_nodes_.at(std::string{name});
    }

    // Returns the vector of all nodes in the graph
    [[nodiscard]] const std::vector<std::shared_ptr<Node>>& GetNodes() const noexcept {
        return nodes_;
    }

private:
    // Stores all nodes in the graph, in order of addition
    // Uses vector for cache locality and sequential access
    std::vector<std::shared_ptr<Node>> nodes_;
    // Maps node names to their shared_ptrs for fast lookup by name
    std::unordered_map<std::string, std::shared_ptr<Node>> named_nodes_;
};

// Type alias for a graph node, simplifying shared_ptr usage
template <typename State>
using Node = std::shared_ptr<typename Graph<State>::Node>;

} // namespace

#endif