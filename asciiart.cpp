#include <vector>
#include <iostream>

#include "asciiart.hpp"
#include "utility.hpp"

namespace ASCIIArt {
    //a table is represented by a vector of vectors of characters

    void print(const Table& table) {
        for (unsigned i = 0; i < table.table.size(); i++) {
            for (unsigned j = 0; j < table.table[i].size(); j++) {
                std::cout << table.table[i][j];
            }
            std::cout << std::endl;
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
}