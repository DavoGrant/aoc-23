#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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


long int runForecast(const std::vector<int>& series, long int forecastValue, const bool& forward) {

    int diff_01 = series[1] - series[0];
    bool constantDiffs = true;
    std::vector<int> diffs;
    for (std::vector<int>::size_type i = 0; i < series.size() - 1; i++) {
        int diff_ij = series[i + 1] - series[i];
        diffs.push_back(diff_ij);
        if (diff_ij != diff_01) constantDiffs = false;
    }

    if (!constantDiffs) {
        if (forward) {
            return runForecast(diffs, forecastValue - diffs[0], false);
        } else {
            return runForecast(diffs, forecastValue + diffs[0], true);
        }
    } else {
        if (forward) {
            return forecastValue - diffs[0];
        } else {
            return forecastValue + diffs[0];
        }
    }
}


long int totalForecasts(const std::string& file_name) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    long int forecastValues = 0;
    std::string line;
    while (getline(f, line)) {
        std::vector<int> history = getIntsFromLine(line);
        forecastValues += runForecast(history, history[0], true);
    }

    return forecastValues;
}


int main() {
    long int result = totalForecasts("data_real.txt");
    std::cout << "Total forecast values = " << result << std::endl;
    return 0;
}
