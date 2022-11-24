#include <vector>
#include <iostream>

#include "asciiart.hpp"
#include "utility.hpp"
#include "media.hpp"

namespace ASCIIArt {
    //a table is represented by a vector of vectors of characters

    void print(const Table& table) {
        for (unsigned i = 0; i < table.table.size(); i++) {
            for (unsigned j = 0; j < table.table[i].size(); j++) {
                std::cout << table.table[i][j] << table.table[i][j];
            }
            std::cout << std::endl;
        }
    }

    void print(const ColoredTable& table) {
        for (unsigned i = 0; i < table.table.size(); i++) {
            for (unsigned j = 0; j < table.table[i].size(); j++) {
                //in order to keep the size of the image, we need to print the character twice
                std::string color = "\033[38;2;" + std::to_string(table.table[i][j].r) + ";" + std::to_string(table.table[i][j].g) + ";" + std::to_string(table.table[i][j].b) + "m";
                std::string chars = std::string(2, table.table[i][j].c);
                std::cout << color << chars;                
            }
            std::cout << "\033[0m" << std::endl;
        }
    }

    void set(Table& table, unsigned x, unsigned y, char c) {
        table.table[y][x] = c;
    }

    char get(const Table& table, unsigned x, unsigned y) {
        return table.table[y][x];
    }

    std::vector<char> getRow(const Table& table, unsigned y) {
        return table.table[y];
    }

    std::vector<char> getColumn(const Table& table, unsigned x) {
        std::vector<char> column;
        for (unsigned i = 0; i < table.table.size(); i++) {
            column.push_back(table.table[i][x]);
        }
        return column;
    }

    Table newTable(std::vector<std::vector<char>> table) {
        Table newTable;
        newTable.table = table;
    }

    Table newTable(std::vector<std::string> table) {
        Table newTable;
        for (unsigned i = 0; i < table.size(); i++) {
            std::vector<char> row;
            for (unsigned j = 0; j < table[i].size(); j++) {
                row.push_back(table[i][j]);
            }
            newTable.table.push_back(row);
        }
    }

    Table newTable(std::string string) {
        //split the string into a vector of vector of characters
        Table table;
        std::vector<std::string> rows = string::split(string, '\n');
        for (unsigned i = 0; i < rows.size(); i++) {
            std::vector<char> row = string::split(rows[i]);
            table.table.push_back(row);
        }
        return table;
    }

    namespace Char{

        //64 characters
        const std::vector<char> chars = {
            ' ', '.', ',', ':', ';', 'i', 'l', '!', 'I', '>', '<', '~', '+', '_', '-', '?', ']', '[', '}', '{', '1', ')', '(', '|', '\\', '/', 't', 'f', 'j', 'r', 'x', 'n', 'u', 'v', 'c', 'z', 'X', 'Y', 'U', 'J', 'C', 'L', 'Q', '0', 'O', 'Z', 'm', 'w', 'q', 'p', 'd', 'b', 'k', 'h', 'a', 'o', '*', '#', 'M', 'W', '8', '%', '&', 'B', '@', '$'
            };

        char fromPixel(const Pixel::Pixel& pixel) {
        //return a character from a pixel
        
        //get the average of the pixel
        unsigned average = (pixel.R + pixel.G + pixel.B) / 3;
        //scale the average to the range of the characters
        unsigned index = average / 4;
        //return the character
        return chars[index];
        }

        Char fromPixel_Colored(const Pixel::Pixel& pixel) {
        //return a character from a pixel
        Char c;
        c.r = pixel.R;
        c.g = pixel.G;
        c.b = pixel.B;
        c.c = fromPixel(pixel);
        return c;
        }
    }

    Table fromImage(const Image::Image& image) {
        //return a table from an image
        Table table;
        for (unsigned i = 0; i < image.table.size(); i++) {
            std::vector<char> row;
            for (unsigned j = 0; j < image.table[i].size(); j++) {
                row.push_back(Char::fromPixel(image.table[i][j]));
            }
            table.table.push_back(row);
        }
        return table;
    }

    ColoredTable fromImage_Colored(const Image::Image& image) {
        //return a table from an image
        ColoredTable table;
        for (unsigned i = 0; i < image.table.size(); i++) {
            std::vector<Char::Char> row;
            for (unsigned j = 0; j < image.table[i].size(); j++) {
                row.push_back(Char::fromPixel_Colored(image.table[i][j]));
            }
            table.table.push_back(row);
        }
        return table;
    }
}