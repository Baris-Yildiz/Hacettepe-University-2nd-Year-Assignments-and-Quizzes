#ifndef kNN_Data_H
#define kNN_Data_H

#include <iostream>
#include <string>
#include <vector>

// Point structure
struct Point {
    std::vector<double> features; // Features of the point
    std::string label;            // Optional label for classification

    // Define constructors as needed
    Point(const std::vector<double>& f, const std::string& l = "") : features(f), label(l) {}
};

// Dataset structure
struct Dataset {
    std::vector<Point> points;    // Points in the dataset
    std::vector<std::string> header; // Header for the dataset
    double threshold;             // Threshold for the dataset

    // Define constructors as needed

    // Default constructor
    Dataset() {};

    // Parameterized constructor
    Dataset(const std::vector<Point>& p, const std::vector<std::string>& h) : points(p), header(h) {}  


};

#endif // kNN_Data_H