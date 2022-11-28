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

std::vector<int> round(std::vector<int> numbers, unsigned length){
    // Round numbers to the nearest possible integer (ex: round([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15], 4) -> [2.5, 6.5, 10.5, 14.5])
    // ex: round([1,2,3,4,5,6,7,8,9], 3) -> [2, 5, 8]
    unsigned short lengthOfNumbers = numbers.size()/length;
    std::vector<int> roundedNumbers;
    unsigned short counter = 0;
    double sum = 0;
    for (unsigned i = 0; i < numbers.size(); i++){
        sum += numbers[i];
        counter++;
        if (counter == lengthOfNumbers){
            roundedNumbers.push_back(sum/lengthOfNumbers);
            counter = 0;
            sum = 0;
        }
    }
    return roundedNumbers;
}


int closer(int value, std::vector<int> numbers){
    // Return the number in numbers that is closest to value
    int closest = numbers[0];
    for (unsigned i = 0; i < numbers.size(); i++){
        if (abs(value - numbers[i]) < abs(value - closest)){
            closest = numbers[i];
        }
    }
    return closest;
}