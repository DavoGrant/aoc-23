#include <iostream>
#include <fstream>


int sumOfCalibrationValues(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    std::unordered_map<std::string, int> numberWords = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            int firstNumber = 0;
            bool firstNumberFound = false;
            for (std::string::size_type i = 0; i < line.size(); i++) {

                if (firstNumberFound) break;

                if (isdigit(line[i])) {
                    firstNumber = line[i] - '0';
                    firstNumberFound = true;
                } else {
                    for (int j = 0; j <= i; j++) {

                        if (firstNumberFound) break;

                        std::string possibleNumber = line.substr(j, i - j + 1);
                        if (numberWords.contains(possibleNumber)) {
                            firstNumber = numberWords[possibleNumber];
                            firstNumberFound = true;
                        }
                    }
                }
            }

            int lastNumber = 0;
            bool lastNumberFound = false;
            for (std::string::size_type i = line.size() - 1; i >=0; i--) {

                if (lastNumberFound) break;

                if (isdigit(line[i])) {
                    lastNumber = line[i] - '0';
                    lastNumberFound = true;
                } else {
                    for (int j = line.size() - i; j > 0; j--) {

                        if (lastNumberFound) break;

                        std::string possibleNumber = line.substr(i, j);
                        if (numberWords.contains(possibleNumber)) {
                            lastNumber = numberWords[possibleNumber];
                            lastNumberFound = true;
                        }
                    }
                }
            }

            sum += firstNumber * 10 + lastNumber;
        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int main() {
    int result = sumOfCalibrationValues("data_real.txt");
    std::cout << "Total calibration values = " << result << std::endl;
    return 0;
}
