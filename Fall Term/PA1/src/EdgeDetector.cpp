// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

// Default constructor
EdgeDetector::EdgeDetector() {
    Gx = new double* [3] {
        new double[3] {-1,0,1},
        new double[3] {-2,0,2},
        new double[3] {-1,0,1}
    };

    Gy = new double * [3] {
            new double[3] {-1,-2,-1},
            new double[3] {0,0,0},
            new double[3] {1,2,1}
    };
}

// Destructor
EdgeDetector::~EdgeDetector() {
    for (int i = 0; i < 3; i++) {
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    std::vector<std::pair<int,int>> edges;

    if (input_image.get_data() == nullptr) {
        return edges;
    }

    ImageMatrix Ix = initializeSobelOperatorWithKernel(Gx, input_image);
    ImageMatrix Iy = initializeSobelOperatorWithKernel(Gy, input_image);

    int height = input_image.get_height();
    int width = input_image.get_width();

    double magnitudes[height*width];

    extractMagnitudes(magnitudes, height, width, Ix, Iy);
    int length = (int) (sizeof(magnitudes) / sizeof(double));

    findEdges(edges, magnitudes, length, width);
    return edges;
}

/*
 * Finds the average of a list consisting of doubles.
 */
double EdgeDetector::averageOfArray(const double *arr, int length) {
    double average = 0;

    for (int i = 0; i < length; i++) {
        average+= arr[i];
    }

    average /= length;
    return average;
}

/*
 * Finds the edges of the image matrix and stores them in "edges".
 */
void EdgeDetector::findEdges(std::vector<std::pair<int, int>> &edges, const double *magnitudes, int length, int width) {
    double threshold = averageOfArray(magnitudes, length);
    for (int i = 0; i < length; i++) {
        if (magnitudes[i] > threshold) {
            edges.emplace_back(i / width,i % width);
        }
    }
}

/*
 * Fills the magnitudes array with all magnitudes in the image matrix.
 */
void EdgeDetector::extractMagnitudes(double* magnitudes, int height, int width, const ImageMatrix& Ix, const ImageMatrix& Iy) {
    int index = 0;
    double** IxData = Ix.get_data();
    double** IyData = Iy.get_data();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double magnitude = sqrt(pow(IxData[i][j],2) + pow(IyData[i][j],2));
            magnitudes[index++] = magnitude;
        }
    }
}

/*
 * Creates an ImageMatrix that represents a sobel operator.
 */
ImageMatrix EdgeDetector::initializeSobelOperatorWithKernel(double** kernel, const ImageMatrix &input_image) {

    Convolution convolutionWithKernel(kernel, 3, 3, 1, true);
    return convolutionWithKernel.convolve(input_image);
}







