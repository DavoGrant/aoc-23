#include <iostream>
#include <fstream>


bool checkAdjacentSameRow(const std::string& line, const int startNumberIdx, const int endNumberIdx) {
    if (startNumberIdx - 1 > 0) {
        if (line[startNumberIdx - 1] != '.') {
            return true;
        }
    }
    if (endNumberIdx + 1 < line.size()) {
        if (line[endNumberIdx + 1] != '.') {
            return true;
        }
    }
    return false;
}


bool checkAdjacentDiffRow(const std::string& line, const int startNumberIdx, const int endNumberIdx) {
    int startBound = std::max(startNumberIdx - 1, 0);
    int endBound = std::min(endNumberIdx + 1, static_cast<int>(line.size() - 1));
    for (std::string::size_type i = startBound; i <= endBound; i++) {
        if (line[i] != '.' && !isdigit(line[i])) {
            return true;
        }
    }
    return false;
}


int sumPart(const std::string& line_a, const std::string& line_b, const std::string& line_c,
            const int startNumberIdx, const int endNumberIdx, const std::string& numberStr) {

    bool isAdjacentAboveRow = checkAdjacentDiffRow(line_a, startNumberIdx, endNumberIdx);
    bool isAdjacentSameRow = checkAdjacentSameRow(line_b, startNumberIdx, endNumberIdx);
    bool isAdjacentBelowRow = checkAdjacentDiffRow(line_c, startNumberIdx, endNumberIdx);

    if (isAdjacentAboveRow || isAdjacentSameRow || isAdjacentBelowRow) {
        return std::stoi(numberStr);
    } else {
        return 0;
    }
}


int sumLineParts(const std::string& line_a, const std::string& line_b, const std::string& line_c) {

    int lineSum = 0;
    int startNumberIdx = 0;
    int endNumberIdx = 0;
    std::string numberStr = "";
    for (std::string::size_type i = 0; i < line_b.size(); i++) {

        if (isdigit(line_b[i]) && numberStr == "") {

            startNumberIdx = i;
            numberStr += line_b[i];
            if (i == line_b.size() - 1) {
                endNumberIdx = i;
                lineSum += sumPart(line_a, line_b, line_c, startNumberIdx, endNumberIdx, numberStr);
            }

        } else if (isdigit(line_b[i])) {

            numberStr += line_b[i];
            if (i == line_b.size() - 1) {
                endNumberIdx = i;
                lineSum += sumPart(line_a, line_b, line_c, startNumberIdx, endNumberIdx, numberStr);
            }

        } else if (numberStr != "") {

            endNumberIdx = i - 1;
            lineSum += sumPart(line_a, line_b, line_c, startNumberIdx, endNumberIdx, numberStr);
            startNumberIdx = 0;
            numberStr = "";
        }
    }
    return lineSum;
}


int sumOfPartNumbers(const std::string& file_name) {

    std::string line_a;
    std::string line_b;
    std::string line_c;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {

        getline(f, line_a);
        getline(f, line_b);

        sum += sumLineParts(line_b, line_a, line_b);  // Top line.
        while (getline(f, line_c)) {

            sum += sumLineParts(line_a, line_b, line_c);  // Main lines.

            line_a = line_b;
            line_b = line_c;
        }
        sum += sumLineParts(line_a, line_b, line_a);  // Last line.

    } else {
        perror("Error opening file");
    }

    return sum;
}


int sumOfGearRatios(const std::string& file_name) {

    std::string line_a;
    std::string line_b;
    std::string line_c;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {

        getline(f, line_a);
        getline(f, line_b);

        sum += sumLineGears(line_b, line_a, line_b);  // Top line.
        while (getline(f, line_c)) {

            sum += sumLineGears(line_a, line_b, line_c);  // Main lines.

            line_a = line_b;
            line_b = line_c;
        }
        sum += sumLine(line_a, line_b, line_a);  // Last line.

    } else {
        perror("Error opening file");
    }

    return sum;
}


int main() {
    int result = sumOfPartNumbers("data_real.txt");
    std::cout << "Total of part numbers = " << result << std::endl;
    return 0;
}
