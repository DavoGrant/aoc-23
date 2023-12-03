#include <iostream>
#include <fstream>


int sumOfGameIDs(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            int gameID = 0;
            for (std::string::size_type i = 0; i < line.size(); i++) {

                if (line[i] == ':') {
                    gameID = std::stoi(line.substr(5, i + 1));
                }
            }
            std::cout << gameID << std::endl;
        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


struct CubeDraw
{
    int number;
    std::string colour;
};


CubeDraw getCubeDrawNumberAndColour(const std::string& line) {
    CubeDraw cubes;
    cubes.number = 0;
    cubes.colour = "blue";

    return cubes;
}


int main() {
    int result = sumOfGameIDs("data_test_1.txt");
    std::cout << "Total game IDs = " << result << std::endl;
    return 0;
}
