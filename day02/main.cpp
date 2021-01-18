#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> split(const std::string& input, const std::string& regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}

std::vector<std::string> vectorify(std::string path)
{
    std::ifstream file(path);

    std::vector<std::string> v;
    std::string val;
    while(std::getline(file, val)) {
        v.push_back(val);
    }
    return v;
}


int main() {
    auto rules = vectorify("/input.txt");
    int validPasswords = 0;

    for (auto & r : rules) {
        // String is split into 4 elements and assigned to the variables below.
        auto x = split(r, "[- ]");

        std::string minValue = x[0];
        std::string maxValue = x[1];
        std::string charToCount = x[2];
        std::string stringToCmp = x[3];

        //remove : from string
        charToCount.erase(remove(charToCount.begin(), charToCount.end(), ':'), charToCount.end());

        // count all the occurrences of the char in the string.
        size_t count = std::count(stringToCmp.begin(), stringToCmp.end(), charToCount.at(0));

        if(count >= std::stoi(minValue) && count <= std::stoi(maxValue))
            ++validPasswords;
    }
    std::cout << validPasswords << std::endl;
}
