#include "ImageProcessor.h"

// Default constructor
ImageProcessor::ImageProcessor() {

}

// Destructor
ImageProcessor::~ImageProcessor() {

}

/*
 * Decodes the hidden message in an image matrix. The applied procedure is:
 * 1. The image matrix gets sharpened.
 * 2. The edge pixels in the sharpened matrix are collected.
 * 3. The message in the image is decoded.
 */
std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {

    if (img.get_data() == nullptr) {
        return "";
    }

    ImageSharpening imageSharpening;
    ImageMatrix sharpenedImage = imageSharpening.sharpen(img, 2);

    EdgeDetector edgeDetector;
    std::vector<std::pair<int,int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);

    DecodeMessage decodeMessage;
    std::string message = decodeMessage.decodeFromImage(sharpenedImage, edgePixels);

    return message;
}

/*
 * Encodes / embeds a hidden message inside an image matrix. The applied procedure is:
 * 1. The image matrix gets sharpened.
 * 2. The edge pixels in the sharpened matrix are collected.
 * 3. The message is encoded into the image.
 */
ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageMatrix resultantMatrix;

    if (img.get_data() == nullptr || message.empty()) {
        return resultantMatrix;
    }

    ImageSharpening imageSharpening;
    ImageMatrix sharpenedImage = imageSharpening.sharpen(img, 2);

    EdgeDetector edgeDetector;
    std::vector<std::pair<int,int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);

    EncodeMessage encodeMessage;
    resultantMatrix = encodeMessage.encodeMessageToImage(img, message, edgePixels);

    return resultantMatrix;
}
