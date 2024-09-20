#ifndef IMAGE_SHARPENING_H
#define IMAGE_SHARPENING_H

#include "ImageMatrix.h"
#include "Convolution.h"

class ImageSharpening {
    public:
        ImageSharpening(); // Default constructor
        ~ImageSharpening(); // Destructor

        ImageMatrix sharpen(const ImageMatrix& input_image, double k);  // Sharpens the image.

    private:

        // Fields for the blurring kernel.
        double** blurring_kernel;
        int kernel_height;
        int kernel_width;
        
        // Clips all values in the matrix to the range [0, 255].
        void clipValuesInMatrix(ImageMatrix &matrix);
};

#endif // IMAGE_SHARPENING_H



