#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage(); // Default Constructor
    ~EncodeMessage(); // Destructor

    // Function to encode a message into an image matrix
    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions);

private:

    // Finds the fibonacci number at a certain index. Assumes that fib(0) = 0 and fib(1) = 1.
    static long long fibonacciNumberAtIndex(int index);

    // Returns a vector that contains every prime number up to and including n.
    std::vector<int> primeNumbersUntil(int n);

    // Modifies the prime indexes of the message by adding a corresponding fibonacci number to the character's ascii code.
    void modifyPrimeIndexes(std::string &message);

    // Applies right circular shifting to the message by length/2 characters.
    void shiftMessage(std::string &message);

    // Embeds the message into the edges pixels of the matrix.
    void embedMessageIntoMatrix(ImageMatrix &image, const std::string &message,
                                const std::vector<std::pair<int, int>> &positions);

    // Clips the value to the printable character range [33,126].
    void clipValue(long long* value);
};

#endif // ENCODE_MESSAGE_H
