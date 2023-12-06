#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::vector<int> getIntsFromLine(const std::string& line) {

    std::istringstream iss(line);
    std::vector<int> numbers;

    int number;
    while (iss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}


int multiplyNumberOfWaysToWin(const std::string& file_name) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    std::string line_time;
    getline(f, line_time);
    std::vector<int> times = getIntsFromLine(line_time.substr(5));

    std::string line_distance;
    getline(f, line_distance);
    std::vector<int> distances = getIntsFromLine(line_distance.substr(9));

    int numberOfWaysToWin = 1;
    for (std::string::size_type i = 0; i < times.size(); i++) {
        float t_1_minus = (times[i] - pow(times[i] * times[i] - (4 * distances[i]), 0.5)) / 2.;
        float t_1_plus = (times[i] + pow(times[i] * times[i] - (4 * distances[i]), 0.5)) / 2.;

        int t_1_minus_int = (std::ceil(t_1_minus) == t_1_minus) ? std::ceil(t_1_minus) + 1 : std::ceil(t_1_minus);
        int t_1_plus_int = (std::floor(t_1_plus) == t_1_plus) ? std::floor(t_1_plus) - 1 : std::floor(t_1_plus);

        numberOfWaysToWin *= t_1_plus_int - t_1_minus_int + 1;
    }

    return numberOfWaysToWin;
}


unsigned long long int concatIntsFromLine(const std::string& line) {

    std::istringstream iss(line);
    std::string numberStr = "";

    std::string number;
    while (iss >> number) {
        numberStr += number;
    }
    std::cout << numberStr << std::endl;

    return std::stoll(numberStr);
}


unsigned long long int waysToWin(const std::string& file_name) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    std::string line_time;
    getline(f, line_time);
    unsigned long long int time = concatIntsFromLine(line_time.substr(5));

    std::string line_distance;
    getline(f, line_distance);
    unsigned long long int distance = concatIntsFromLine(line_distance.substr(9));

    double t_1_minus = (time - pow(time * time - (4 * distance), 0.5)) / 2.;
    double t_1_plus = (time + pow(time * time - (4 * distance), 0.5)) / 2.;

    unsigned long long int t_1_minus_int = (std::ceil(t_1_minus) == t_1_minus) ? std::ceil(t_1_minus) + 1 : std::ceil(t_1_minus);
    unsigned long long int t_1_plus_int = (std::floor(t_1_plus) == t_1_plus) ? std::floor(t_1_plus) - 1 : std::floor(t_1_plus);

    return t_1_plus_int - t_1_minus_int + 1;
}


int main() {
    int result_1 = multiplyNumberOfWaysToWin("data_real.txt");
    std::cout << "Multiplied n ways to win = " << result_1 << std::endl;
    unsigned long long int result_2 = waysToWin("data_real.txt");
    std::cout << "Ways to win (big race) = " << result_2 << std::endl;
    return 0;
}
