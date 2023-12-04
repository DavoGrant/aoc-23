#include <iostream>
#include <fstream>
#include <set>


int sumScratchPoints(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            std::string numberStr = "";
            bool winningNumbersSegment = false;
            bool playerNumbersSegment = false;
            std::set <int> winningNumbers;
            int nMatches = 0;
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
            sum += pow(2, nMatches - 1);
        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int main() {
    int result = sumScratchPoints("data_real.txt");
    std::cout << "Total of scratch points = " << result << std::endl;
    return 0;
}
