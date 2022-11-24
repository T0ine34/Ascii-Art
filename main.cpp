#include <vector>
#include <string>
#include <iostream>

#include "asciiart.hpp"
#include "utility.hpp"
#include "media.hpp"

int main(int argc, char** argv){
    std::string path = argv[1];
    Image::Image image = Image::newImage(path);

    //resize with coefficient argv[2] if set
    if (argc > 2){
        float coefficient = std::stof(argv[2]);
        Image::resize(image, coefficient);
    }

    Image::print(image);
    return 0;
}