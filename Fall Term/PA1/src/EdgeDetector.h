    #ifndef EDGE_DETECTOR_H
    #define EDGE_DETECTOR_H

    #include "ImageMatrix.h"
    #include "Convolution.h"
    #include <vector>

    class EdgeDetector {
        public:
            EdgeDetector(); // Default constructor
            ~EdgeDetector(); // Destructor

            // Detect edges in the imageMatrix
            std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

        private:
            // Sobel operators.
            double** Gx;
            double** Gy;

            // Finds the average of a list consisting of doubles.
            double averageOfArray(const double* arr, int length);

            // Finds the edges of the image matrix and stores them in "edges".
            void findEdges(std::vector<std::pair<int, int>> &edges, const double *magnitudes, int length, int width);

            //Fills the magnitudes array with all magnitudes in the image matrix.
            void extractMagnitudes(double *magnitudes, int height, int width, const ImageMatrix &Ix, const ImageMatrix &Iy);

            // Creates an ImageMatrix that represents a sobel operator.
            ImageMatrix initializeSobelOperatorWithKernel(double **kernel, const ImageMatrix &input_image);

    };

    #endif // EDGE_DETECTOR_H


