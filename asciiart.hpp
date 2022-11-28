#ifndef __ASCIIART_HPP__
#define __ASCIIART_HPP__

#include <vector>
#include <string>
#include "media.hpp"


namespace ASCIIArt {
    //a table is represented by a vector of vectors of characters

    namespace Char{

        struct Char {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        char c;
        };

        std::vector<char>getchars(unsigned n);

        char fromPixel(const Pixel::Pixel& pixel, const std::vector<char>& characters);

        Char fromPixel_Colored(const Pixel::Pixel& pixel, const std::vector<char>& characters);

    }

    struct Table {
        std::vector<std::vector<char>> table;
    };

    struct ColoredTable {
        std::vector<std::vector<Char::Char>> table;
    };

    void print(const Table& table);
    void print(const ColoredTable& table);

    void set(Table& table, unsigned x, unsigned y, char c);

    char get(const Table& table, unsigned x, unsigned y);

    std::vector<char> getRow(const Table& table, unsigned y);

    std::vector<char> getColumn(const Table& table, unsigned x);

    Table newTable(std::vector<std::vector<char>> table);
    Table newTable(std::vector<std::string> table);
    Table newTable(std::string table);
    
    Table fromImage(const Image::Image& image, unsigned char nb_chars);

    ColoredTable fromImage_Colored(const Image::Image& image, unsigned char nb_chars);
}

#endif