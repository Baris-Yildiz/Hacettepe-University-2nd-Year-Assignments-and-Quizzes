// ImageLoader.h

#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>
#include <vector>

class ImageLoader {
public:
    ImageLoader(const std::string& filepath); // Constructor for loading image from file
    ImageLoader(const ImageLoader &other); // copy constructor
    ImageLoader& operator=(const ImageLoader &other); // copy assignment operator

    // Destructor
    ~ImageLoader();


    int getHeight() const;
    int getWidth() const;
    double** getImageData() const;

private:
    int height;
    int width;
    double** imageData;
};

#endif // IMAGE_LOADER_H
