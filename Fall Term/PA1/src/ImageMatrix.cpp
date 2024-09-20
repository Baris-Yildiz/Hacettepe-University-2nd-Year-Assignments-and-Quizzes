#include "ImageMatrix.h"
#include "ImageLoader.h"


// Default constructor
ImageMatrix::ImageMatrix() : height(0), width(0), data(nullptr){

}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    initializeData();
}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    initializeData(const_cast<const double**>(imageData));
}

// Destructor
ImageMatrix::~ImageMatrix() {
    deleteData();
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth){
    initializeData(inputMatrix);
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) : height(other.height), width(other.width){
    initializeData(const_cast<const double**>(other.data));
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {

    if (this == &other) {
        return *this;
    }

    //deallocate the memory space of the old data.
    deleteData();

    //copy the data of the operand.
    height = other.height;
    width = other.width;

    initializeData(const_cast<const double**>(other.data));

    return *this;
}

// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix first(*this);


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            first.data[i][j] += other.data[i][j];
        }
    }

    return first;

}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {

    ImageMatrix first(*this);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            first.data[i][j] -= other.data[i][j];
        }
    }

    return first;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {

    ImageMatrix first(*this);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            first.data[i][j] *= scalar;
        }
    }

    return first;
}

// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {

    if (i < 0 || j < 0) {
        return -1;
    }

    if (i > height-1 || j > width-1) {
        return -1;
    }

    return data[i][j];
}

/*
 * Getter function to access the height of the image matrix.
 */
int ImageMatrix::get_height() const {
    return height;
}

/*
 * Getter function to access the width of the image matrix.
 */
int ImageMatrix::get_width() const {
    return width;
}

/*
 * Fills the data with zeros.
 */
void ImageMatrix::initializeData() {
    data = new double * [height];

    for (int i = 0; i < height; i++) {
        data[i] = new double [width];
        for (int j = 0; j < width; j++) {
            data[i][j] = 0;
        }
    }
}

/*
 * Fills the data with the data of fillMatrix (given as parameter).
 */
void ImageMatrix::initializeData(const double **fillMatrix) {
    data = new double * [height];

    for (int i = 0; i < height; i++) {
        data[i] = new double [width];
        for (int j = 0; j < width; j++) {
            data[i][j] = fillMatrix[i][j];
        }
    }
}

/*
 * Deletes the data of the image matrix.
 */
void ImageMatrix::deleteData() {
    if (data != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] data[i];
        }
    }
    delete[] data;
}