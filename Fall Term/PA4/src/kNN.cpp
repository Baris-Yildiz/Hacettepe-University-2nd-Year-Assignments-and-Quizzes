#include "kNN.h"

// Constructor implementation
KNN::KNN(int neighbors, double threshold) : k(neighbors), split_threshold(threshold) {
}

// Train function implementation
void KNN::train(Dataset& data) {
    // standardize the data

    // build the KD_Tree

}

// Predict function implementation
int KNN::predict(const Point& queryPoint) {
    // returns if the given queryPoint is habitable (1) or not (0)
}

// Additional methods or helper functions can be added as needed
