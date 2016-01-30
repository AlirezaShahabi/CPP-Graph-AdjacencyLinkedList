
// a linkedlist representing the adjacent neighbors

#ifndef NEIGHBORLIST_H
#define NEIBORLIST_H

#include <iostream>
#include <vector>
#include <utility>

class NeighborList {
template <typename U> friend class Graph;
private:
    struct Node {
        size_t index;
        int weight;
        Node* next;
        Node(size_t i, int w):index(i), weight(w), next(nullptr) {}
        Node():index(0), weight(0), next(nullptr) {}
    };
    Node* head;
    size_t length;
    // private utility functions
    void copy_helper(Node*, Node*&);
    void delete_helper(Node*&);
    
public:
    NeighborList();
    NeighborList(const NeighborList&);
    ~NeighborList();
    
    void add_node(size_t, int);
    void rem_node(size_t);
    
    void return_index(std::vector<std::pair<size_t, int>>&) const;
    bool find_node(size_t) const;
};

#endif


