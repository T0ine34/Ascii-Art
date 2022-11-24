#include <vector>
#include <string>
#include <iostream>


#include "media.hpp"
#include "asciiart.hpp"

int main(int argc, char** argv){

    if (argc < 1){
        std::cout << "Usage: " << argv[0] << " <image path> <mode> <coefficient> OR " << argv[0] << " <option>" << std::endl;
        std::cout << "Use -h or --help for more information" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    if (option == "-h" || option == "--help"){
        std::cout << "Usage: " << argv[0] << " <image path> <mode> <coefficient> OR " << argv[0] << " <option>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -h, --help: Show this help message" << std::endl;
        std::cout << "    -v, --version: Show version information" << std::endl;
        std::cout << "Modes:" << std::endl;
        std::cout << "    colored: Print colored image" << std::endl;
        std::cout << "    ascii: Print image as ascii art" << std::endl;
        std::cout << "    ascii-colored: Print colored image as ascii art" << std::endl;

        return 0;
    }

    if (option == "-v" || option == "--version"){
        std::cout << "Version: 1.1.0" << std::endl;
        return 0;
    }

    std::string path = argv[1];
    Image::Image image = Image::newImage(path);

    //mode is in 2nd argument (colored, ascii or ascii_colored)
    std::string mode = argv[2];

    //resize with coefficient argv[2] if set
    if (argc > 3){
        float coefficient = std::stof(argv[3]);
        Image::resize(image, coefficient);
    }

    if (mode == "colored"){
        Image::print(image);
    } else if (mode == "ascii"){
        ASCIIArt::Table t = ASCIIArt::fromImage(image);
        ASCIIArt::print(t);
    } else if (mode == "ascii_colored"){
        ASCIIArt::ColoredTable t = ASCIIArt::fromImage_Colored(image);
        ASCIIArt::print(t);
        ;
    } else {
        std::cout << "Invalid mode" << std::endl;
    }
    
    return 0;
}