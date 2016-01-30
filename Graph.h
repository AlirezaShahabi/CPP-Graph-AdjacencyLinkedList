
// vertices are represented with array
// edges and neighbors are represented through a linked list

// best representation if graph is sparse

#ifndef GRAPH_H
#define GRAPH_H

#include "NeighborList.h"
#include <vector>
#include <stack>
#include <algorithm>

template <typename T> class Graph {

private:
    std::vector<T> vertices;
    std::vector<NeighborList> neighbors;
    size_t n_vertices;
    // private utility function
    void update_neighbors();
    size_t find_index(const T&) const;
    void dfs(size_t, std::vector<bool>&, std::ostream&) const;
    void bfs(size_t, std::vector<bool>&, std::ostream&, size_t) const;
    
public:
    Graph();
    void add_vertex(const T&);
    void add_edge(const T&, const T&, int);
    void rem_edge(const T&, const T&);
    void find_adj_vertices(const T&, std::ostream&) const;
    bool check_connection(const T&, const T&) const;
    void depth_first_search(size_t, std::ostream&) const;
    void breadth_first_search(size_t, std::ostream&) const;
};

#endif


// constructor
template <typename T> Graph<T>::Graph():vertices(), neighbors(),
n_vertices(0) {};

// add a new vertex
template <typename T> void Graph<T>::add_vertex(const T& obj) {
    vertices.push_back(obj);
    ++n_vertices;
    update_neighbors();
}

// add a new edge
template <typename T>
void Graph<T>::add_edge(const T& obj1, const T& obj2, int weight) {
    size_t i1 = find_index(obj1);
    size_t i2 = find_index(obj2);
    if (i1 < n_vertices && i2 < n_vertices) {
        neighbors[i1].add_node(i2, weight);
        neighbors[i2].add_node(i1, weight);
    }
}

// remove an existing edge
template <typename T>
void Graph<T>::rem_edge(const T& obj1, const T& obj2) {
    size_t i1 = find_index(obj1);
    size_t i2 = find_index(obj2);
    if (i1 < n_vertices && i2 < n_vertices) {
        neighbors[i1].rem_node(i2);
        neighbors[i2].rem_node(i1);
    }
}

// find adjacent vertices to curr vertex
// Time:        O(n_vertices)
// Extra space: O(n_vertices + 2*n_edges)
template <typename T>
void Graph<T>::find_adj_vertices(const T& obj, std::ostream& os) const {
    size_t i = find_index(obj);
    if (i < n_vertices) {
        std::vector<std::pair<size_t, int>> index_list;
        neighbors[i].return_index(index_list);
        if (index_list.empty()) {
            os << "no neighbor !" << std::endl;
        } else {
            for (const auto& a:index_list) {
                os << vertices[a.first] << ", weight: " << a.second;
                os << "   ";
            }
            os << std::endl;
        }
    }
}

// check if two vertices are connected
template <typename T>
bool Graph<T>::check_connection(const T& obj1, const T& obj2) const {
    size_t i1 = find_index(obj1);
    size_t i2 = find_index(obj2);
    if (i1 < n_vertices && i2 < n_vertices) {
        return neighbors[i1].find_node(i2);
    }
    return false;
}

// perform a depth first search on graph
// Time: O(2 * n_edges)
template <typename T>
void Graph<T>::depth_first_search(size_t start_i, std::ostream& os) const {
    if (start_i < n_vertices) {
        std::vector<bool> visited(n_vertices, 0);
        dfs(start_i, visited, os);
        os << std::endl;
    } else {
        os << "index out of bound" << std::endl;
    }
}

// perform a breadth first search on graph
template <typename T>
void Graph<T>::breadth_first_search(size_t start_i, std::ostream& os) const {
    if (start_i < n_vertices) {
        std::vector<bool> visited(n_vertices, 0);
        visited[start_i] = 1;
        os << vertices[start_i] << "  ";
        size_t n_visit = 1;
        bfs(start_i, visited, os, n_visit);
        os << std::endl;
    } else {
        os << "index out of bound" << std::endl;
    }
}


// private utility functions


// update the neighbors vector when a new vertex is added
template <typename T> void Graph<T>::update_neighbors() {
    neighbors.push_back(NeighborList());
}

// find the index
template <typename T> size_t Graph<T>::find_index(const T& obj) const {
    size_t index = std::find(vertices.begin(), vertices.end(), obj)
                   - vertices.begin();
    return index;
}

// depth first search
template <typename T>
void Graph<T>::dfs(size_t i, std::vector<bool>& visited, std::ostream& os)
const {
    visited[i] = 1;
    os << vertices[i] << "  ";
    NeighborList::Node* next_check = neighbors[i].head;
    while (next_check) {
        if (!visited[next_check->index]) {
            dfs(next_check->index, visited, os);
        }
        next_check = next_check->next;
    }
}

// breadth first search
template <typename T>
void Graph<T>::bfs(size_t i, std::vector<bool>& visited, std::ostream& os,
size_t n_visit) const {
    NeighborList::Node* p1 = neighbors[i].head;
    NeighborList::Node* p2 = p1;
    while (p2) {
        if (!visited[p2->index]) {
            visited[p2->index] = 1;
            ++n_visit;
            os << vertices[p2->index] << "  "; 
        }
        p2 = p2->next;
    }
    if (n_visit < n_vertices) {bfs(p1->index, visited, os, n_visit);}
}




