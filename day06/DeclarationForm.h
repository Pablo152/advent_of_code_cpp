#pragma once

#include <vector>
#include <string>

class DeclarationForm {
public:
	DeclarationForm(std::vector<std::string> personData) {
		for (const auto& person : personData) {
			personsData.push_back(person);
		}
	}

	void setCountShared(int n) {
		countShared += n;
	}

	int getCountShared() {
		return countShared;
	}

	std::vector<std::string> getPersonsData() {
		return personsData;
	}
private:
	std::vector<std::string> personsData;
	int countShared{ 0 };
};