#include <iostream>
#include <fstream>


int sumOfCalibrationValues(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            int firstNumber = 0;
            for (std::string::size_type i = 0; i < line.size(); i++) {
                if (isdigit(line[i]) ){
                    firstNumber = line[i] - '0';
                    break;
                }
            }

            int lastNumber = 0;
            for (std::string::size_type i = line.size() - 1; i >=0; i--) {
                if (isdigit(line[i]) ){
                    lastNumber = line[i] - '0';
                    break;
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
