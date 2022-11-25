#include <string>
#include <vector>
#include <iostream>

namespace string{
    std::vector<std::string> split(std::string string, char delimiter){
        std::vector<std::string> strings;
        std::string currentString;
        for (unsigned i = 0; i < string.size(); i++){
            if (string[i] == delimiter){
                strings.push_back(currentString);
                currentString = "";
            } else {
                currentString += string[i];
            }
        }
        strings.push_back(currentString);
        return strings;
    }

    std::vector<char> split(std::string string){
        std::vector<char> characters;
        for (unsigned i = 0; i < string.size(); i++){
            characters.push_back(string[i]);
        }
        return characters;
    }
}
