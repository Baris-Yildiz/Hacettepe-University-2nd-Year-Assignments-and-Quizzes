#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "ImageSharpening.h"
#include "EdgeDetector.h"
#include "DecodeMessage.h"
#include "ImageMatrix.h"
#include "EncodeMessage.h"

#include <vector>

class ImageProcessor {
    public:
        ImageProcessor(); // Default constructor
        ~ImageProcessor(); // Destructor

        // Decodes the hidden message in an image matrix.
        std::string decodeHiddenMessage(const ImageMatrix &img);

        // Encodes / embeds a hidden message inside an image matrix.
        ImageMatrix encodeHiddenMessage(const ImageMatrix &img, const std::string &message);
};

#endif // IMAGE_PROCESSOR_H



