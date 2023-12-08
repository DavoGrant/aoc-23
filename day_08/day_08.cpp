#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


std::unordered_map<char, int> directionIndexs = {{'L', 0}, {'R', 1}};


long int totalSteps(const std::string& file_name) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    std::string directions;
    getline(f, directions);

    std::string line;
    getline(f, line);
    std::unordered_map<std::string, std::vector<std::string>> map;
    std::vector<std::string> locations;
    while (getline(f, line)) {
        map[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
        if (line[2] == 'A') {
            locations.push_back(line.substr(0, 3));
        }
    }

    long int nSteps = 0;
    int dirIdx = 0;
    while (true) {

        if (nSteps % 10000 == 0) {
            for (const auto &element : locations) {
                std::cout << element << " ";
            }
            std::cout << "steps = "<< nSteps << std::endl;
        }

        bool madeIt = true;
        for (std::vector<std::string>::size_type i = 0; i < locations.size(); i++) {
            if (locations[i][2] != 'Z') madeIt = false;
            locations[i] = map[locations[i]][directionIndexs[directions[dirIdx]]];
        }
        if (madeIt) return nSteps;
        nSteps += 1;
        if (dirIdx < directions.size() - 1) {
            dirIdx += 1;
        } else {
            dirIdx = 0;
        }
    }

    return 0;
}


int main() {
    long int result = totalSteps("data_real.txt");
    std::cout << "Total steps = " << result << std::endl;
    return 0;
}
