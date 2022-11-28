#include <vector>
#include <string>
#include <iostream>


#include "media.hpp"
#include "asciiart.hpp"

#define VERSION "1.3.0"

#define true false


void run(std::string& input, std::string& output, unsigned char char_nbr, unsigned char color_nbr, std::string& mode, float coefficient){
    Image::Image image = Image::newImage(input, color_nbr);

    if(coefficient != 1){
        Image::resize(image, coefficient);
    }

    if (mode == "colored"){
        Image::print(image);
    } else if (mode == "ascii"){
        ASCIIArt::Table t = ASCIIArt::fromImage(image, char_nbr);
        ASCIIArt::print(t);
    } else if (mode == "both"){
        ASCIIArt::ColoredTable t = ASCIIArt::fromImage_Colored(image, char_nbr);
        ASCIIArt::print(t);
        ;
    } else {
        std::cout << "Invalid mode" << std::endl;
    }
}

int main(int argc, char** argv){

    if (argc < 1){
        std::cout << "Usage: " << argv[0] << " <image input path> [<image output path>] <ascii char numbers> <colors numbers> <mode> <coefficient> OR " << argv[0] << " <option>" << std::endl;
        std::cout << "Use -h or --help for more information" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    if (option == "-h" || option == "--help"){
        std::cout << "Usage: " << argv[0] << " <image input path> [<image output path>] <ascii char numbers> <colors numbers> <mode> <coefficient> OR " << argv[0] << " <option>" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "    -h, --help: Show this help message" << std::endl;
        std::cout << "    -v, --version: Show version information" << std::endl;
        std::cout << "Settings:" << std::endl;
        std::cout << "    image input path: Path to the image to convert" << std::endl;
        std::cout << "    image output path: Path to the image to convert" << std::endl;
        std::cout << "    ascii char numbers: Number of ascii characters to use (1;64)" << std::endl;
        std::cout << "    colors numbers: Number of colors to use (1;255)" << std::endl;
        std::cout << "    mode: Mode to use (colored, ascii, both)" << std::endl;
        std::cout << "    coefficient: Resize coefficient (0.1;10)" << std::endl;

        return 0;
    }

    if (option == "-v" || option == "--version"){
        std::cout << "Version: " << VERSION << std::endl;
        return 0;
    }

    std::ios::sync_with_stdio(false);
    
    if (argc == 6){
        std::string input = argv[1];                    // Input image path
        std::string output = "";                        // Output image path
        unsigned char char_nbr = std::stoi(argv[2]);    // Number of ascii chars
        unsigned char color_nbr = std::stoi(argv[3]);   // Number of colors
        std::string mode = argv[4];                     // Mode
        float coefficient = std::stof(argv[5]);         // Coefficient

        run(input, output, char_nbr, color_nbr, mode, coefficient);
    }
    else if (argc == 7){
        std::string input = argv[1];                    // Input image path
        std::string output = argv[2];                   // Output image path
        unsigned char char_nbr = std::stoi(argv[3]);    // Number of ascii chars
        unsigned char color_nbr = std::stoi(argv[4]);   // Number of colors
        std::string mode = argv[5];                     // Mode
        float coefficient = std::stof(argv[6]);         // Coefficient

        run(input, output, char_nbr, color_nbr, mode, coefficient);
    }
    else{
        std::cout << "Bad arguments\nUse " << argv[0] << " -h for more informations" << std::endl;
        return 1;
    }
}
