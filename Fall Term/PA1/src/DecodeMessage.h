#ifndef DECODE_MESSAGE_H
#define DECODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

// Class `DecodeMessage`: Provides the functionality to decode a binary message into an ASCII representation.
class DecodeMessage {
    public:
        // Constructors and destructors
        DecodeMessage(); // Default constructor
        ~DecodeMessage(); // Destructor

        // Takes an image matrix and decodes the message hidden inside it.
        std::string decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels);
    
    private:

        // Pads the string with leading zeros so that the resultant string's length is the nearest multiple of seven.
        void padString(std::stringstream &stream, const std::vector<std::pair<int, int>> &edgePixels);

        // Extracts every least significant bit of the edge values of the image.
        void extractLeastSignificantBitsToString(std::stringstream &stream, const ImageMatrix &image,
                                 const std::vector<std::pair<int, int>> &edgePixels);

        // Decodes the string that consists of bits created by the least significant bits of edge pixels.
        std::string decodeMessage(std::stringstream &stream, int length);

        // Clips an ascii value to the range [33,126].
        void clipValue(int* value);
};

#endif // DECODE_MESSAGE_H
