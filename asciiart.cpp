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
                std::cout << table.table[i][j] << table.table[i][j] << table.table[i][j];
            }
            std::cout << std::endl;
        }
    }

    void print(const ColoredTable& table) {
        for (unsigned i = 0; i < table.table.size(); i++) {
            Pixel::Pixel last = {0, 0, 0};
            for (unsigned j = 0; j < table.table[i].size(); j++) {
                //in order to keep the size of the image, we need to print the character twice
                if (last.R != table.table[i][j].r || last.R != table.table[i][j].g || last.B != table.table[i][j].b) {
                    std::cout << "\033[38;2;" << (int)table.table[i][j].r << ";" << (int)table.table[i][j].g << ";" << (int)table.table[i][j].b << "m";
                    last = {table.table[i][j].r, table.table[i][j].g, table.table[i][j].b};
                }
                std::cout << std::string(3, table.table[i][j].c);                
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
        return newTable;
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
        return newTable;
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

        std::vector<char> getchars(unsigned n) {
            //return a vector of n chars representing the entire range of chars (take it regularly)
            if (n == 64) {
                return chars;
            }
            std::vector<char> chars;
            int space = 64 / n;
            for (unsigned i = 0; i < n; i++) {
                chars.push_back(ASCIIArt::Char::chars[i * space]);
            }
            return chars;
        }

        char fromPixel(const Pixel::Pixel& pixel, const std::vector<char>& chars) {
            //return the char that represents the pixel
            //the chars are ordered from the darkest to the lightest
            //the pixel is represented by a number between 0 and 255
            //the chars are represented by a number between 0 and chars.size() - 1
            //the pixel is divided by 255 / (chars.size() - 1) to get the char
            return chars[(int)(pixel.R / (255.0 / (chars.size() - 1)))];
        }

        Char fromPixel_Colored(const Pixel::Pixel& pixel, const std::vector<char>& chars) {
            //return a character from a pixel
            Char c;
            c.r = pixel.R;
            c.g = pixel.G;
            c.b = pixel.B;
            c.c = fromPixel(pixel, chars);
            return c;
        }
    }

    Table fromImage(const Image::Image& image, unsigned char char_nbr) {
        //return a table from an image
        std::vector<char> chars = Char::getchars(char_nbr);
        Table table;
        for (unsigned i = 0; i < image.table.size(); i++) {
            std::vector<char> row;
            for (unsigned j = 0; j < image.table[i].size(); j++) {
                row.push_back(Char::fromPixel(image.table[i][j], chars));
            }
            table.table.push_back(row);
        }
        return table;
    }

    ColoredTable fromImage_Colored(const Image::Image& image, unsigned char char_nbr) {
        //return a table from an image
        ColoredTable table;
        for (unsigned i = 0; i < image.table.size(); i++) { 
            std::vector<Char::Char> row;
            for (unsigned j = 0; j < image.table[i].size(); j++) {
                row.push_back(Char::fromPixel_Colored(image.table[i][j], Char::getchars(char_nbr)));
            }
            table.table.push_back(row);
        }
        return table;
    }
}
