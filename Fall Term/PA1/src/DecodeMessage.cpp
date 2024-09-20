// DecodeMessage.cpp

#include "DecodeMessage.h"
#include "sstream"
#include "cmath"

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

// Takes an image matrix and decodes the message hidden inside it.
std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    if (image.get_data() == nullptr || edgePixels.empty()) {
        return "";
    }

    std::stringstream binaryString("");

    padString(binaryString, edgePixels);
    extractLeastSignificantBitsToString(binaryString, image ,edgePixels);
    std::string message = decodeMessage(binaryString, (int)binaryString.str().size());

    return message;
}

/*
 * Pads the string with leading zeros so that the resultant string's length is the nearest multiple of seven.
 * The string is passed as a stringstream reference and so the changes are saved, not returned as a new string.
 */
void DecodeMessage::padString(std::stringstream &stream, const std::vector<std::pair<int, int>>& edgePixels) {

    int zerosToAdd = (edgePixels.size() % 7 == 0) ? 0 : 7 - ((int)edgePixels.size() % 7);
    for (int i = 0; i < zerosToAdd; i++) {
        stream << "0";
    }
}

/*
 * Extracts every least significant bit of the edge values of the image.
 */
void DecodeMessage::extractLeastSignificantBitsToString(std::stringstream &stream, const ImageMatrix &image, const std::vector<std::pair<int, int>>& edgePixels) {
    for (std::pair<int,int> pair: edgePixels) {
        auto value = (long long) image.get_data(pair.first, pair.second);
        stream << std::to_string(value % 2);
    }
}

/*
 * Decodes the string that consists of bits created by the least significant bits of edge pixels.
 * Reads starting from the left, 7 characters at a time.
 */
std::string DecodeMessage::decodeMessage(std::stringstream& stream, int length) {

    char bit;
    int asciiValue = 0;

    std::stringstream message("");

    for (int i = 0; i < length; i+=7) {
        for (int j = 0; j < 7; j++) {
            stream >> bit;
            if (bit == '1') {
                asciiValue += (int) pow(2, 6-j);
            }
        }

        clipValue(&asciiValue);
        message << char(asciiValue);

        asciiValue = 0;
    }

    return message.str();
}

/*
 * Clips an ascii value to the range [33,126]. This range represents the ascii values
 * of the printable characters.
 */
void DecodeMessage::clipValue(int *value) {
    int val = *value;

    if (val <= 32) {
        val += 33;
    }

    if (val >= 127) {
        val = 126;
    }

    *value = val;
}
