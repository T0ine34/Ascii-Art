#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <vector>
#include <string>

namespace string{
    std::vector<std::string> split(std::string string, char delimiter);

    std::vector<char> split(std::string string);
}

#endif