#include "EncodeMessage.h"
#include <cmath>
#include "bitset"


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {

    if (positions.empty() || img.get_data() == nullptr || message.empty()) {
        return img;
    }

    std::string modifiedMessage = message;

    modifyPrimeIndexes(modifiedMessage);
    shiftMessage(modifiedMessage);
    embedMessageIntoMatrix(const_cast<ImageMatrix &>(img), modifiedMessage, positions);

    return img;
}

/*
 * Finds the fibonacci number at a certain index. Assumes that fib(0) = 0 and fib(1) = 1.
 * Returns a long long because the fibonacci numbers grow fast.
 */
long long EncodeMessage::fibonacciNumberAtIndex(int index) {
    if (index < 0) {
        return -1;
    }

    if (index == 0) {
        return 0;
    }

    long long previousFibonacciNumber = 1;
    long long smallerPreviousFibonacciNumber = 0;
    long long fibonacciNumber = 1;

    for (int i = 1; i < index; i++) {
        fibonacciNumber = previousFibonacciNumber + smallerPreviousFibonacciNumber;
        smallerPreviousFibonacciNumber = previousFibonacciNumber;
        previousFibonacciNumber = fibonacciNumber;
    }


    return fibonacciNumber;
}

/*
 * Returns a vector that contains every prime number up to and including n.
 */
std::vector<int> EncodeMessage::primeNumbersUntil(int n) {

    std::vector<int> primes;

    if (n < 2) {
        return primes;
    }

    primes.push_back(2);

    bool isPrime;
    for (int i = 3; i < n; i+=2) {
        isPrime = true;
        for (int j = 2; j <= sqrt(i); j++) {

            if (i % j == 0) {
                isPrime = false;
                break;
            }

        }

        if (isPrime) {
            primes.push_back(i);
        }

    }

    return primes;
}

/*
 * Goes through every character at the prime indexes of the string and
 * adds the fibonacci number of that index to that characters ascii value.
 */
void EncodeMessage::modifyPrimeIndexes(std::string& message) {

    int length = (int)message.length();
    std::vector<int> primes = primeNumbersUntil(length);

    for (int prime: primes) {
        long long fibToAdd = fibonacciNumberAtIndex(prime);
        unsigned char c = message[prime];
        int originalAscii = c;

        long long newAscii = originalAscii + fibToAdd;
        clipValue(&newAscii);

        message[prime] = (char)newAscii;
    }
}

/*
 * Applies right circular shifting to the message by length/2 characters.
 */
void EncodeMessage::shiftMessage(std::string& message) {
    if (message.length() == 1) {
        return;
    }

    int length = (int) message.length();
    int shiftBy = length / 2;

    message = message.substr(length - shiftBy) + message.substr(0, length - shiftBy);
}

/*
 * Embeds the message into the edges pixels of the matrix. For this, it manipulates the least significant bits of the edge pixel values.
 */
void EncodeMessage::embedMessageIntoMatrix(ImageMatrix& image, const std::string& message, const std::vector<std::pair<int, int>>& positions) {

    int length = (int)message.length();
    int pairPosition = 0;

    double** imageData = image.get_data();


    for (int i = 0; i < length; i++) {
        unsigned char c = message[i];
        auto charBits = std::bitset<7>(c);

        for (int j = 0; j < 7; j++) {
            bool bitToEmbed = charBits[j];

            if (pairPosition >= positions.size()) {
                return;
            }

            std::pair<int,int> pair = positions[pairPosition++];

            int pixelValue = (int)image.get_data(pair.first,pair.second);

            if (bitToEmbed && (pixelValue % 2 == 0) ) {
                imageData[pair.first][pair.second]++;
            } else if(!bitToEmbed && (pixelValue % 2 == 1)) {
                imageData[pair.first][pair.second]--;
            }
        }
    }
}

/*
 * Clips the value to the printable character range [33,126].
 */
void EncodeMessage::clipValue(long long int *value) {
    long long val = *value;

    if (val <= 32) {
        val+=33;
    } else if (val >= 127) {
        val = 126;
    }

    *value = val;
}

