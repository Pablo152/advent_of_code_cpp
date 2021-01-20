#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::vector<char>> vectorify(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<char>> input;
    std::string line;
    while(std::getline(file, line)){
        std::vector<char> temp;
        for ( char &c : line) {
            temp.push_back(c);
        }
        input.emplace_back(std::move(temp));
    }
    return input;
}

int trees(const std::vector<std::vector<char>> &map, unsigned int slopeX, unsigned int slopeY) {
    unsigned int x = 0;
    unsigned int y = 0;
    int tree_count = 0;

    while(y < map.size()) {
        if(map.at(y).at(x) == '#') {
            ++tree_count;
        }
        x += slopeX;
        y += slopeY;
        x = x % map[0].size();
    }
    return tree_count;
}


int main() {
    std::vector<std::vector<char>> map = vectorify("../input.txt");
    std::cout << "result 1:" << trees(map, 3, 1) << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> slopes = {{1,1}, {3,1}, {5,1}, {7, 1}, {1, 2}};
    unsigned int result = 1;
    for (auto &slope : slopes) {
        result *= trees(map, slope.first, slope.second);
    }

    std::cout << "result 2: " << result << std::endl;

    return 0;

}