#ifndef __ASCIIART_HPP__
#define __ASCIIART_HPP__

#include <vector>
#include <string>


namespace ASCIIArt {
    //a table is represented by a vector of vectors of characters

    struct Table {
        std::vector<std::vector<char>> table;
    };

    void print(const Table& table);

    void set(Table& table, unsigned x, unsigned y, char c);

    char get(const Table& table, unsigned x, unsigned y);

    std::vector<char> getRow(const Table& table, unsigned y);

    std::vector<char> getColumn(const Table& table, unsigned x);

    Table newTable(std::vector<std::vector<char>> table);
    Table newTable(std::vector<std::string> table);
    Table newTable(std::string table);
}

#endif