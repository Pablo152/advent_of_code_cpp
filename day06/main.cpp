#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "DeclarationForm.h"

std::string implode(const std::string& glue, const std::vector<std::string>& pieces)
{
	std::string a;
	size_t leng = pieces.size();
	for (int i = 0; i < leng; i++)
	{
		a += pieces[i];
		if (i < (leng - 1))
			a += glue;
	}
	return a;
}

size_t countDistinct(const std::string& s)
{

	std::unordered_map<char, int> m;

	for (int i = 0; i < s.length(); i++) {
		m[s[i]]++;
	}

	return m.size();
}

std::vector<DeclarationForm> readAndParseFile()
{
	std::ifstream file{ "C:\\Users\\Administrador\\source\\repos\\ConsoleApplication4\\Debug\\input.txt" };

	if (!file) {
		std::cerr << "File was not found in the given location." << std::endl;
	}

	std::string x;
	std::vector<std::string> groups;
	std::vector<DeclarationForm> declarationForms;
	while (std::getline(file, x)) {
		if (x == "") {
			DeclarationForm declaration(groups);
			declarationForms.push_back(declaration);
			groups.clear();
			continue;
		}
		groups.push_back(x);
	}

	DeclarationForm declaration(groups);
	declarationForms.push_back(declaration);

	return declarationForms;
}

size_t solution_1(std::vector<DeclarationForm>& declarationForms) {
	size_t totalSum = 0;
	for (auto& x : declarationForms) {
		const std::vector<std::string> personData{ x.getPersonsData() };
		const std::string implodedPerson{ implode("", personData) };
		totalSum += countDistinct(implodedPerson);
	}
	return totalSum;
}

int main()
{
	std::vector<DeclarationForm> declarationForms{ readAndParseFile() };
	const size_t totalSum{ solution_1(declarationForms) };

	std::cout << "Total sum is: " << totalSum << std::endl;

	return 1;
}