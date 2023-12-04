#include <iostream>
#include <fstream>
#include <set>


int numMatches(const std::string& line) {

    int nMatches = 0;
    std::string numberStr = "";
    bool winningNumbersSegment = false;
    bool playerNumbersSegment = false;
    std::set <int> winningNumbers;
    for (std::string::size_type i = 0; i < line.size(); i++) {

        if (line[i] == ':') {
            winningNumbersSegment = true;
        }

        if (winningNumbersSegment) {
            if (isdigit(line[i])) {
                numberStr += line[i];
            } else if (numberStr != "") {
                winningNumbers.insert(std::stoi(numberStr));
                numberStr = "";
            }
        }

        if (line[i] == '|') {
            winningNumbersSegment = false;
            playerNumbersSegment = true;
        }

        if (playerNumbersSegment) {
            if (isdigit(line[i])) {
                numberStr += line[i];
            } else if (numberStr != "") {
                int checkNum = std::stoi(numberStr);
                numberStr = "";
                if(winningNumbers.find(checkNum) != winningNumbers.end()){
                    nMatches += 1;
                }
            }
        }

        if (i == line.size() - 1 && numberStr != "") {
            int checkNum = std::stoi(numberStr);
            numberStr = "";
            if(winningNumbers.find(checkNum) != winningNumbers.end()){
                nMatches += 1;
            }
        }
    }
    return nMatches;
}

int sumScratchPoints(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {
            int nMatches = numMatches(line);
            if (nMatches > 0) {
                sum += pow(2, nMatches - 1);
            }
        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int sumNLinesRecursive(std::ifstream& f, int nLines) {

    int sum = 0;
    std::string line;
    int nLinesComplete = 0;
    while (getline(f, line) && ++nLinesComplete <= nLines) {
        std::streampos fPos = f.tellg();

        int nMatches = numMatches(line);
        sum += 1 + sumNLinesRecursive(f, nMatches);

        f.clear();
        f.seekg(fPos);
    }
    return sum;
}


int sumScratchCards(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            std::streampos fPos = f.tellg();

            int nMatches = numMatches(line);
            int recursiveMatches = sumNLinesRecursive(f, nMatches);
            sum += 1 + recursiveMatches;

            f.clear();
            f.seekg(fPos);
        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int main() {
    int result_1 = sumScratchPoints("data_real.txt");
    std::cout << "Total of scratch points = " << result_1 << std::endl;
    int result_2 = sumScratchCards("data_real.txt");
    std::cout << "Total of scratch cards = " << result_2 << std::endl;
    return 0;
}
