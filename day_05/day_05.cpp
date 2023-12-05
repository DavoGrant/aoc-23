#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::vector<long int> getSeedNumbers(std::ifstream& f) {

    std::string line;
    getline(f, line);
    std::vector<long int> seedNumbers;
    std::istringstream iss(line.substr(6));

    long int seedNumber;
    while (iss >> seedNumber) {
        seedNumbers.push_back(seedNumber);
    }

    return seedNumbers;
}


struct MapRange
{
    long int sourceRangeStart;
    long int sourceRangeEnd;
    long int destinationRangeStart;
    long int destinationRangeEnd;
};


MapRange getMapRange(const std::string& line) {

    std::istringstream iss(line);
    std::vector<long int> rangeValues;

    long int rangeValue;
    while (iss >> rangeValue) {
        rangeValues.push_back(rangeValue);
    }

    MapRange mapping;
    mapping.sourceRangeStart = rangeValues[1];
    mapping.sourceRangeEnd = rangeValues[1] + rangeValues[2] - 1;
    mapping.destinationRangeStart = rangeValues[0];
    mapping.destinationRangeEnd = rangeValues[0] + rangeValues[2] - 1;

    return mapping;
}


long int nearestLocation(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    if (!f.is_open()) {
        perror("Error opening file");
    }

    std::vector<long int> mapNumbers = getSeedNumbers(f);
    std::vector<bool> mapNumbersUpdated(mapNumbers.size(), false);
    while (getline(f, line)) {

        if (line.find("map") != std::string::npos) {
            continue;
        } else if (line.size() == 0) {
            for (std::vector<long int>::size_type i = 0; i < mapNumbers.size(); i++) {
                mapNumbersUpdated[i] = false;
            }
            continue;
        } else {
            MapRange mapping = getMapRange(line);
            for (std::vector<long int>::size_type i = 0; i < mapNumbers.size(); i++) {
                if (!mapNumbersUpdated[i] && mapNumbers[i] >= mapping.sourceRangeStart && mapNumbers[i] <= mapping.sourceRangeEnd) {
                    mapNumbers[i] = mapping.destinationRangeStart + mapNumbers[i] - mapping.sourceRangeStart;
                    mapNumbersUpdated[i] = true;
                }
            }
        }
    }

    long int nearest = *std::min_element(mapNumbers.begin(), mapNumbers.end());

    return nearest;
}


int main() {
    long int result = nearestLocation("data_test_1.txt");
    std::cout << "Nearest location = " << result << std::endl;
    return 0;
}
