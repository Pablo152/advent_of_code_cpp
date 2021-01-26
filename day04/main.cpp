#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &input,
                               const std::string &regex) {
  // passing -1 as the submatch index parameter performs splitting
  std::regex re(regex);
  std::sregex_token_iterator first{input.begin(), input.end(), re, -1}, last;
  return {first, last};
}

class Passport {
public:
  Passport(std::string passportStr) {
    std::vector<std::string> splittedStr = split(passportStr, " ");
    Setter(splittedStr);
  }

  bool AllValidFields() {
    return !(byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() ||
             hcl.empty() || ecl.empty() || pid.empty());

  }

  bool ValidByr() { return std::stoi(byr) >= 1920 && std::stoi(byr) <= 2002; }

  bool ValidIyr() { return std::stoi(iyr) >= 2010 && std::stoi(iyr) <= 2020; }

  bool ValidEyr() { return std::stoi(eyr) >= 2020 && std::stoi(eyr) <= 2030; }

  bool ValidHgt() {

    if  (hgt.find("cm") != std::string::npos && std::stoi(hgt) >= 150 &&
        std::stoi(hgt) <= 193) {
      return true;
    }

    if  (hgt.find("in") != std::string::npos && std::stoi(hgt) >= 59 && std::stoi(hgt) <= 76) {
      return true;
    }

    return false;
  }

  bool ValidHcl() {
        bool valid = false;
        std::string value = hcl.substr(1, hcl.size());
        if (hcl[0] == '#' && value.size() == 6) {
            std::stoi(value, 0, 16);
            valid = true;
        }
        return valid;
  }

  bool ValidEcl() {
    return std::regex_match(ecl, std::regex("amb|blu|brn|gry|grn|hzl|oth"));
  }

  bool ValidPid() { return pid.size() == 9;  }

  bool AllValid2() {
    if (!AllValidFields()) {
      return false;
    }

    return ValidByr() && ValidEcl() && ValidEyr() && ValidHcl() && ValidHgt() &&
            ValidIyr() && ValidPid();
  }

private:
  /*
  The expected fields are as follows:
      byr (Birth Year)
      iyr (Issue Year)
      eyr (Expiration Year)
      hgt (Height)
      hcl (Hair Color)
      ecl (Eye Color)
      pid (Passport ID)
      cid (Country ID)
  */
  std::string byr;
  std::string iyr;
  std::string eyr;
  std::string hgt;
  std::string hcl;
  std::string ecl;
  std::string pid;

  void Setter(std::vector<std::string> splittedStr) {

    for (auto &str : splittedStr) {
      std::vector<std::string> tokenizedStrings = split(str, ":");
      if (tokenizedStrings.at(0) == "hcl") {
        hcl = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "ecl") {
        ecl = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "byr") {
        byr = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "iyr") {
        iyr = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "eyr") {
        eyr = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "hgt") {
        hgt = tokenizedStrings.at(1);
      } else if (tokenizedStrings.at(0) == "pid") {
        pid = tokenizedStrings.at(1);
      }
    }
  }
};

/*
function parses file from:
ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

to:
ecl:gry pid:860033327 eyr:2020 hcl:#fffffd byr:1937 iyr:2017 cid:147 hgt:183cm
*/

std::vector<Passport> parse_file(std::string path) {
  std::vector<Passport> passports;

  std::ifstream infile(path);

  std::string input;
  std::string line;
  while (std::getline(infile, line)) {
    if (line != "") {
      input += line + " ";
    } else {
      passports.emplace_back(std::move(input));
      input = "";
    }
  }
  passports.emplace_back(std::move(input));
  return passports;
}

unsigned int solution_1(std::vector<Passport> passports) {
  unsigned int count = 0;
  for (auto &passport : passports) {
    if (passport.AllValidFields())
      ++count;
  }
  return count;
}

unsigned int solution_2(std::vector<Passport> passports) {
  unsigned int count = 0;
  for (auto &passport : passports) {
    if (passport.AllValid2())
      ++count;
  }
  return count;
}

int main() {
  std::vector<Passport> parsedInput = parse_file("./input.txt");

  std::cout << "solution 1: " << solution_1(parsedInput) << std::endl;
  std::cout << "solution 2: " << solution_2(parsedInput) << std::endl;

  return 0;
}
