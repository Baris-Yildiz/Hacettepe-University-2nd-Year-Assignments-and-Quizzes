// Convolution.h

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageMatrix.h"

// Class `Convolution`: Provides the functionality to convolve an image with
// a kernel. Padding is a bool variable, indicating whether to use zero padding or not.
class Convolution {
public:
    // Constructors and destructors
    Convolution(); // Default constructor
    Convolution(double** customKernel, int kernelHeight, int kernelWidth, int stride, bool padding); // Parametrized constructor for custom kernel and other parameters
    ~Convolution(); // Destructor

    Convolution(const Convolution &other); // Copy constructor
    Convolution& operator=(const Convolution &other); // Copy assignment operator

    ImageMatrix convolve(const ImageMatrix& input_image) const; // Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.

private:
    // Add any private member variables and functions .

    //fields needed for convolution.
    double** kernel;
    int kernelHeight;
    int kernelWidth;
    int stride;
    bool padding;

    //Fills the kernel with the values in customKernel (given as parameter).
    void initializeKernel(const double** customKernel);

    //Fills the non-padded area of a matrix with the values in fillWith (given as parameter).
    void fillNonPaddedArea(ImageMatrix &matrixToFill, const ImageMatrix &fillWith) const;

    //Performs the convolution operation to the mainMatrix, stores the resultant matrix in outputMatrix.
    void convolveMatrix(ImageMatrix &mainMatrix, ImageMatrix &output) const;
};

#endif // CONVOLUTION_H
