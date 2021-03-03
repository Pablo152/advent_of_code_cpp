#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

const std::vector<std::string> readFromFile(const std::string& pathToFile)
{
	std::vector<std::string> lines;

	std::ifstream file{ pathToFile };
	if (!file) {
		std::cerr << "File not found" << std::endl;
	}

	std::string x;
	while (std::getline(file, x)) {
		lines.push_back(x);
	}
	return lines;
}

int parseLine(const std::string& line)
{
	int start{ 0 };
	int end{ 127 };

	std::string rowChars{ line.substr(0, 8) };
	for (const char& c : rowChars) {
		if (c == 'F') {
			end = ((start + end + 1) / 2) - 1;
		}
		else if (c == 'B') {
			start = ((start + end + 1) / 2);
		}
	}

	const int row{ start };
	int columnStart{ 0 };
	int columnEnd{ 7 };

	std::string columnChars{ line.substr(6, line.size()) };
	for (const char& c : columnChars) {
		if (c == 'L') {
			columnEnd = ((columnStart + columnEnd + 1) / 2) - 1;
		}
		else if (c == 'R') {
			columnStart = ((columnStart + columnEnd + 1) / 2);
		}
	}

	const int col{ columnStart };
	return (row * 8) + col;
}

const int solution_2(std::vector<int>& seatIds)
{
	std::sort(seatIds.begin(), seatIds.end());
	for (int i = 1; i < seatIds.size(); ++i)
		if (seatIds[i - 1] + 1 != seatIds[i])
			return seatIds[i] - 1;

	return -1;
}

int main()
{
	const std::vector<std::string> rows{ readFromFile("input.txt") };
	std::vector<int> seatIds;

	for (const std::string& row : rows) {
		seatIds.push_back(parseLine(row));
	}

	const auto maxEl{ std::max_element(seatIds.begin(), seatIds.end()) };
	std::cout << "Max seat id is: " << *maxEl << std::endl;
	std::cout << "Solution 2 is: " << solution_2(seatIds) << std::endl;

	return 1;
}