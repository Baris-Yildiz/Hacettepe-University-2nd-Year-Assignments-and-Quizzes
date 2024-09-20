// ImageLoader.cpp

#include "ImageLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>


// Default constructor
ImageLoader::ImageLoader(const std::string& filepath) : height(0), width(0), imageData(nullptr) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<double>> tempImageData;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double pixel;
        while (iss >> pixel) {
            row.push_back(pixel);
        }
        tempImageData.push_back(row);
    }

    file.close();

    height = static_cast<int>(tempImageData.size());
    if (height == 0) {
        std::cerr << "Error: Empty image data." << std::endl;
        return;
    }

    width = static_cast<int>(tempImageData[0].size());

    // Allocate memory for imageData and copy data
    imageData = new double*[height];
    for (int i = 0; i < height; ++i) {
        imageData[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            imageData[i][j] = tempImageData[i][j];
        }
    }
}

// copy constructor
ImageLoader::ImageLoader(const ImageLoader &other) : height(other.height), width(other.width) {
    // Allocate memory for the matrix and copy data
    imageData = new double*[height];
    for (int i = 0; i < height; ++i) {
        imageData[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            imageData[i][j] = other.imageData[i][j];
        }
    }
}


// copy assignment operator
ImageLoader& ImageLoader::operator=(const ImageLoader &other) {
    if (this == &other) {
        return *this; // self-assignment check
    }

    // Deallocate old memory
    if (imageData != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] imageData[i];
        }
    }
    delete[] imageData;

    // Copy from other
    height = other.height;
    width = other.width;
    imageData = new double*[height];
    for (int i = 0; i < height; ++i) {
        imageData[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            imageData[i][j] = other.imageData[i][j];
        }
    }

    return *this;
}

// destructor
ImageLoader::~ImageLoader() {
    // Deallocate memory
    if (imageData != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] imageData[i];
        }
    }
    delete[] imageData;
}


int ImageLoader::getHeight() const {
    return height;
}

int ImageLoader::getWidth() const {
    return width;
}

double** ImageLoader::getImageData() const {
    return imageData;
}

