#ifndef __MEDIA_HPP__
#define __MEDIA_HPP__

#include <vector>
#include <string>

namespace Pixel{
    struct Pixel{
        unsigned char R = 0;
        unsigned char G = 0;
        unsigned char B = 0;
    };

    Pixel newPixel(unsigned char R, unsigned char G, unsigned char B);

    unsigned char get(const Pixel& pixel, unsigned char channel);

    void set(Pixel& pixel, unsigned char channel, unsigned char value);

    void set(Pixel& pixel, unsigned char R, unsigned char G, unsigned char B);

    void print(const Pixel& pixel);

    void repr(const Pixel& pixel);

    void print_last();

    void repr_last();

    void reset_last();
}

namespace Image{
    struct Image{
        std::vector<std::vector<Pixel::Pixel>> table;
    };

    void print(const Image& image);

    Pixel::Pixel get(const Image& image, unsigned x, unsigned y);

    std::vector<Pixel::Pixel> getRow(const Image& image, unsigned y);

    std::vector<Pixel::Pixel> getColumn(const Image& image, unsigned x);

    void insert(Image& image, std::vector<Pixel::Pixel> row, unsigned y = -1);

    void insert(Image& image, Pixel::Pixel pixel, unsigned x = -1, unsigned y = -1);

    Image newImage(std::string path, unsigned nb_colors = 256);

    void resize(Image& image, float coefficient);
}

#endif