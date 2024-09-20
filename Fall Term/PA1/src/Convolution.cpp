#include "Convolution.h"

// Default constructor 
Convolution::Convolution() : kernel(nullptr), kernelHeight(0), kernelWidth(0), stride(0), padding(false) {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad): kernelHeight(kh),
kernelWidth(kw), stride(stride_val), padding(pad){
    initializeKernel(const_cast<const double **>(customKernel));
}

// Destructor
Convolution::~Convolution() {
    //release the dynamically allocated space for kernel
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; i++) {
            delete[] kernel[i];
        }
    }
    delete[] kernel;
}

// Copy constructor
Convolution::Convolution(const Convolution &other) : stride(other.stride), padding(other.padding), kernelHeight(other.kernelHeight), kernelWidth(other.kernelWidth){
    initializeKernel(const_cast<const double **>(other.kernel));
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {

    //self-assignment check
    if (this == &other) {
        return *this;
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    initializeKernel(const_cast<const double **>(other.kernel));

    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    if (input_image.get_data() == nullptr) {
        ImageMatrix nullMatrix;
        return nullMatrix;
    }

    ImageMatrix mainMatrix(const_cast<const double **>(input_image.get_data()), input_image.get_height(), input_image.get_width());

    int outputHeight = ((input_image.get_height() - kernelHeight + 2 * padding) / stride) + 1;
    int outputWidth = ((input_image.get_width() - kernelWidth + 2 * padding) / stride) + 1;


    ImageMatrix outputMatrix(outputHeight, outputWidth);

    if (padding) {
        ImageMatrix paddedMainMatrix(mainMatrix.get_height()+2, mainMatrix.get_width()+2);
        mainMatrix = paddedMainMatrix;
        fillNonPaddedArea(mainMatrix, input_image);
    }

    convolveMatrix(mainMatrix, outputMatrix);

    ImageMatrix result(const_cast<const double **>(outputMatrix.get_data()), outputHeight, outputWidth);

    return result;
}

/*
 * Fills the kernel with the values in customKernel (given as parameter).
 */
void Convolution::initializeKernel(const double** customKernel) {

    kernel = new double*[kernelHeight];

    for (int i = 0; i < kernelHeight; i++) {
        kernel[i] = new double[kernelWidth];
    }

    for (int i = 0; i < kernelHeight; i++) {
        for (int j = 0; j < kernelWidth; j++) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

/*
 * Fills the non-padded area of a matrix with the values in fillWith (given as parameter).
 */
void Convolution::fillNonPaddedArea(ImageMatrix &matrixToFill, const ImageMatrix &fillWith) const{
    double** fillData = fillWith.get_data();
    double** mainData = matrixToFill.get_data();

    for (int i = 1; i < matrixToFill.get_height() - 1; i++) {
        for (int j = 1; j < matrixToFill.get_width() - 1; j++) {
            mainData[i][j] = fillData[i-1][j-1];
        }
    }
}

/*
 * Performs the convolution operation to the mainMatrix,
 * uses the kernel field of the Convolution class as the kernel.
 *
 * Stores the output in the output parameter.
 */
void Convolution::convolveMatrix(ImageMatrix& mainMatrix, ImageMatrix& output) const{
    double** outputData = output.get_data();
    double** mainData = mainMatrix.get_data();

    for (int i = 0; i < mainMatrix.get_height() - (kernelHeight-1); i+=stride) {
        for (int j = 0; j < mainMatrix.get_width() - (kernelWidth-1); j+=stride) {
            double sumOfProducts = 0;
            for (int k = 0; k < kernelHeight; k++) {
                for (int l = 0; l < kernelWidth; l++) {
                    sumOfProducts += kernel[k][l] * mainData[i+k][j+l];
                }
            }

            outputData[i / stride][j / stride] = sumOfProducts;
        }
    }
}
