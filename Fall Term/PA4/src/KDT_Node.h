#ifndef KD_TREE_NODES_H
#define KD_TREE_NODES_H

#include "kNN_Data.h"
#include <string>
#include <vector>

// Base Node Class
class KDTreeNode {
public:
    virtual ~KDTreeNode()  {}; // virtual destructor
    virtual bool isLeaf() const = 0; // returns if the node is a leaf node or not

};

class kd_tree_inter_node : public KDTreeNode {
public:
    int split_dimension;
    double split_value;
    KDTreeNode* left;
    KDTreeNode* right;

    // Constructor declaration etc
    kd_tree_inter_node(int split_dimension, double split_value)
            : split_dimension(split_dimension), split_value(split_value), left(nullptr), right(nullptr) {}

    bool isLeaf() const override {
        return false;
    }

    ~kd_tree_inter_node() override {

    }


};

// Leaf Node Class
class kd_tree_leaf_node : public KDTreeNode {
public:
    // Members:
    Dataset data;

    // Constructor declaration
    kd_tree_leaf_node(Dataset dataLabelPairs) : data(dataLabelPairs) {}

    // Overridden virtual methods
    bool isLeaf() const override {
        return true; // Leaf node
    }

    ~kd_tree_leaf_node() override {

    }
};

#endif // KD_TREE_NODES_H