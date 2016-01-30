
#include "NeighborList.h"

// constructor
NeighborList::NeighborList():head(nullptr), length(0) {}

// copy constructor
NeighborList::NeighborList(const NeighborList& rhs):
head(nullptr), length(rhs.length) {
    if (rhs.head) {copy_helper(rhs.head, head);}
}

// destructor
NeighborList::~NeighborList() {if (head) {delete_helper(head);}}

// add a new node to linkedlist
void NeighborList::add_node(size_t index, int weight) {
    Node* new_node = new Node(index, weight);
    if (!head) {
        head = new_node;
    } else {
        Node* temp = head;
        new_node->next = temp;
        head = new_node;
    }
    ++length;
}

// remove a node from linkedlist (find with index)
void NeighborList::rem_node(size_t index) {
    if (!head) {return;}
    if (head->index == index) {
        Node* delNode = head;
        head = head->next;
        delNode->next = nullptr;
        delete delNode;
        --length;
    } else {
        Node* p1 = head;
        Node* p2 = head->next;
        while (p2 && p2->index != index) {
            p1 = p2;
            p2 = p2->next;
        }
        if (p2) {
            Node* delNode = p2;
            p1->next = p2->next;
            delNode->next = nullptr;
            delete delNode;
            --length;
        }
    }
}

// return all the indexes in the linked list
void NeighborList::return_index(std::vector<std::pair<size_t,
    int>>& v) const {
    Node* p = head;
    while (p) {
        v.push_back(std::make_pair(p->index, p->weight));
        p = p->next;
    }
}

// check if a node exists in the linkedlist
bool NeighborList::find_node(size_t index) const {
    if (!head) {return false;}
    Node* p = head;
    while (p && p->index != index) {p = p->next;}
    return p ? true:false;
}

// private utility functions

// make a deep copy
void NeighborList::copy_helper(Node* source, Node*& target) {
    Node* creator = new Node(source->index, source->weight);
    Node* iterator = source->next;
    target = creator;
    while (iterator) {
        creator->next = new Node(iterator->index, iterator->weight);
        creator = creator->next;
        iterator = iterator->next;
    }
}

// delete all the nodes starting at curr
void NeighborList::delete_helper(Node*& curr) {
    while (curr) {
        Node* delNode = curr;
        curr = curr->next;
        delNode->next = nullptr;
        delete delNode;
    }
}


