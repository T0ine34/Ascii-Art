#include <vector>
#include <string>
#include <iostream>

#include "media.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Pixel{
    Pixel newPixel(unsigned char R, unsigned char G, unsigned char B){
        Pixel pixel;
        pixel.R = R;
        pixel.G = G;
        pixel.B = B;
        return pixel;
    }
    
    Pixel Last = newPixel(0, 0, 0);

    unsigned char get(const Pixel& pixel, unsigned char channel){
        switch (channel){
            case 0:
                return pixel.R;
            case 1:
                return pixel.G;
            case 2:
                return pixel.B;
            default:
                return 0;
        }
    }

    void set(Pixel& pixel, unsigned char channel, unsigned char value){
        switch (channel){
            case 0:
                pixel.R = value;
                break;
            case 1:
                pixel.G = value;
                break;
            case 2:
                pixel.B = value;
                break;
        }
    }

    void set(Pixel& pixel, unsigned char R, unsigned char G, unsigned char B){
        pixel.R = R;
        pixel.G = G;
        pixel.B = B;
    }

    void print(const Pixel& pixel){
        //std::cout << "\033[48;2;" << (int)pixel.R << ";" << (int)pixel.G << ";" << (int)pixel.B << "m" << "   " << "\033[0m";
        if (pixel.R != Last.R || pixel.G != Last.G || pixel.B != Last.B){
            std::cout << "\033[48;2;" << (int)pixel.R << ";" << (int)pixel.G << ";" << (int)pixel.B << "m";
            Last.R = pixel.R;
            Last.G = pixel.G;
            Last.B = pixel.B;
        }
        std::cout << "   ";
    }

    void repr(const Pixel& pixel){
        std::cout << "Pixel(" << (int)pixel.R << ", " << (int)pixel.G << ", " << (int)pixel.B << ")";
    }

    void print_last(){
        std::cout << "\033[48;2;" << (int)Last.R << ";" << (int)Last.G << ";" << (int)Last.B << "m" << "   " << "\033[0m";
    }

    void repr_last(){
        std::cout << "Pixel(" << (int)Last.R << ", " << (int)Last.G << ", " << (int)Last.B << ")";
    }

    void reset_last(){
        Last.R = 0;
        Last.G = 0;
        Last.B = 0;
    }
}

namespace Image{
    void print(const Image& image){
        for (unsigned i = 0; i < image.table.size(); i++){
            Pixel::reset_last();
            unsigned j = 0;
            for (j = 0; j < image.table[i].size(); j++){
                Pixel::print(image.table[i][j]);
            }
            std::cout << "\033[0m" << std::endl;
        }
    }

    Pixel::Pixel get(const Image& image, unsigned x, unsigned y){
        return image.table[y][x];
    }

    std::vector<Pixel::Pixel> getRow(const Image& image, unsigned y){
        return image.table[y];
    }

    std::vector<Pixel::Pixel> getColumn(const Image& image, unsigned x){
        std::vector<Pixel::Pixel> column;
        for (unsigned i = 0; i < image.table.size(); i++){
            column.push_back(image.table[i][x]);
        }
        return column;
    }

    void insert(Image& image, std::vector<Pixel::Pixel> row, unsigned y){
        if (y == -1){
            image.table.push_back(row);
        } else {
            image.table.insert(image.table.begin() + y, row);
        }
    }

    void insert(Image& image, Pixel::Pixel pixel, unsigned x, unsigned y){
        if (x == -1 && y == -1){
            image.table[image.table.size() - 1].push_back(pixel);
        } else if (x == -1){
            image.table[y].push_back(pixel);
        } else if (y == -1){
            image.table[image.table.size() - 1].insert(image.table[image.table.size() - 1].begin() + x, pixel);
        } else {
            image.table[y].insert(image.table[y].begin() + x, pixel);
        }
    }

    Image newImage(std::string path){
        // Open the file, then get all the pixels and put them in a vector of vectors of pixels.
        // Then return the image.

        int width, height, channels;
        uint8_t* rgb_image = stbi_load(path.c_str(), &width, &height, &channels, 3);
        std::cout << "Image size: " << width << "x" << height << std::endl;

        Image image;

        for (unsigned i = 0; i < height; i++){
            std::vector<Pixel::Pixel> row;
            for (unsigned j = 0; j < width; j++){
                row.push_back(Pixel::newPixel(rgb_image[i * width * 3 + j * 3], rgb_image[i * width * 3 + j * 3 + 1], rgb_image[i * width * 3 + j * 3 + 2]));
            }
            image.table.push_back(row);
        }

        stbi_image_free(rgb_image);

        return image;
    }

    void resize(Image& image, float coefficient){
        // Resize the image to the given width and height.
        //The image will be resized by adding or removing rows and columns.
        //We don't add blank pixels, we ajust the size of the image, so the image will be distorted.

        unsigned newWidth = image.table[0].size() * coefficient;
        unsigned newHeight = image.table.size() * coefficient;

        std::vector<std::vector<Pixel::Pixel>> newTable;

        for (unsigned i = 0; i < newHeight; i++){
            std::vector<Pixel::Pixel> row;
            for (unsigned j = 0; j < newWidth; j++){
                row.push_back(image.table[i / coefficient][j / coefficient]);
            }
            newTable.push_back(row);
        }

        image.table = newTable;
    }
}