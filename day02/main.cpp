#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
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
    auto rules = vectorify("./input.txt");
    int validPasswords = 0;

    for (auto & r : rules) {
        auto x = split(r, "[- ]");
        x[2].erase(remove(x[2].begin(), x[2].end(), ':'), x[2].end()); //remove : from string
        size_t count = std::count(x[3].begin(), x[3].end(), x[2].at(0));

        if(count >= std::stoi(x[0]) && count <= std::stoi(x[1]))
            ++validPasswords;
    }
    std::cout << validPasswords << std::endl;
}
