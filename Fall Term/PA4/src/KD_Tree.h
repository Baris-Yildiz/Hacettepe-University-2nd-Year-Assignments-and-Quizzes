#ifndef KD_TREE_H
#define KD_TREE_H

#include "KDT_Node.h"
#include "kNN_Data.h"

#include <vector>
#include <iostream>

class KD_Tree {
private:
    KDTreeNode* root;
    double split_threshold; // determines when to stop splitting, ie, stop growing the tree
    
public:
    
    KD_Tree(); // default constructor, sets the split_threshold to 0.1
    KD_Tree(double split_threshold); // parameterized constructor - split_threshold
    ~KD_Tree();

    void build(Dataset& data);
    KDTreeNode* getRoot();

};

#endif // KD_TREE_H