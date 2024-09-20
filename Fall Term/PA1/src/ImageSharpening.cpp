#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() : kernel_height(3), kernel_width(3){
    blurring_kernel = new double *[3]{
            new double[3] {(1.0/9.0),(1.0/9.0),(1.0/9.0)},
            new double[3] {(1.0/9.0),(1.0/9.0),(1.0/9.0)},
            new double[3] {(1.0/9.0),(1.0/9.0),(1.0/9.0)}
    };
}

// Destructor
ImageSharpening::~ImageSharpening(){
    if (blurring_kernel != nullptr) {
        for (int i = 0; i < kernel_height; i++) {
            delete[] blurring_kernel[i];
        }
    }
    delete[] blurring_kernel;
}

/*
 * Sharpens the image.
 */
ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    ImageMatrix sharpenedMatrix;

    if (input_image.get_data() == nullptr) {
        return sharpenedMatrix;
    }

    // Blurs the image first.
    Convolution convolution(blurring_kernel, kernel_height, kernel_width,1,true);

    ImageMatrix blurredMatrix;
    blurredMatrix = convolution.convolve(input_image);

    // Sharpens the image using the original and blurred image.
    sharpenedMatrix = input_image + (input_image - blurredMatrix) * k;

    clipValuesInMatrix(sharpenedMatrix);
    return sharpenedMatrix;
}

/*
 * Clips all values in the matrix to the range [0, 255].
 */
void ImageSharpening::clipValuesInMatrix(ImageMatrix& matrix) {
    double** matrixData = matrix.get_data();
    for (int i = 0; i < matrix.get_height(); i++) {
        for (int j = 0; j < matrix.get_width(); j++) {
            if (matrixData[i][j] > 255) {
                matrixData[i][j] = 255;
            } else if (matrixData[i][j] < 0){
                matrixData[i][j] = 0;
            }
        }
    }
}
