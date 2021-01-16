#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::ifstream file("../input.txt");
    std::vector<int> lines;
    const int target = 2020;

    int x;
    while (file >> x) {
        lines.push_back(x);
    }

    for (int i = 0; i < lines.size(); i++) {
        int sno = target - lines[i];
        for (int j = i + 1; j < lines.size(); j++ ) {
            if(lines[j] == sno) {
                std::cout << lines[i] << " " << lines[j] << std::endl;
                std::cout << "Product is: " << lines[i] * lines[j];
            }
        }
    }
}
