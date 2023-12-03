#include <iostream>
#include <fstream>


struct CubeDraw
{
    int number;
    std::string colour;
};


CubeDraw getCubeDrawNumberAndColour(const std::string& drawLabel) {

    CubeDraw cubes;
    for (std::string::size_type i = 0; i < drawLabel.size(); i++) {
        if (drawLabel[i] == ' ') {
            cubes.number = std::stoi(drawLabel.substr(0, i));
            cubes.colour = drawLabel.substr(i + 1, drawLabel.size() - i + 1);
            break;
        }
    }

    return cubes;
}


int sumOfGameIDs(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            int gameID = 0;
            bool gamePossible = true;
            int lastSpaceIdx = 0;
            for (std::string::size_type i = 0; i < line.size(); i++) {

                if (line[i] == ':') {
                    gameID = std::stoi(line.substr(5, i + 1));
                    lastSpaceIdx = i + 1;
                }

                if (line[i] == ',' || line[i] == ';' || i == line.size() - 1) {

                    int endLineBump = (i == line.size() - 1) ? 1 : 0;
                    std::string drawLabel = line.substr(lastSpaceIdx + 1, i - lastSpaceIdx - 1 + endLineBump);
                    CubeDraw cubes = getCubeDrawNumberAndColour(drawLabel);
                    lastSpaceIdx = i + 1;

                    if (cubes.colour == "red" && cubes.number > 12) {
                        gamePossible = false;
                    } if (cubes.colour == "green" && cubes.number > 13) {
                        gamePossible = false;
                    } else if (cubes.colour == "blue" && cubes.number > 14) {
                        gamePossible = false;
                    }
                }
            }

            if (gamePossible) sum += gameID;

        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int sumOfGamePowers(const std::string& file_name) {

    std::string line;
    std::ifstream f (file_name);

    int sum = 0;
    if (f.is_open()) {
        while (getline(f, line)) {

            int redMin = 0;
            int greeMin = 0;
            int blueMin = 0;
            int lastSpaceIdx = 0;
            for (std::string::size_type i = 0; i < line.size(); i++) {

                if (line[i] == ':') {
                    lastSpaceIdx = i + 1;
                }

                if (line[i] == ',' || line[i] == ';' || i == line.size() - 1) {

                    int endLineBump = (i == line.size() - 1) ? 1 : 0;
                    std::string drawLabel = line.substr(lastSpaceIdx + 1, i - lastSpaceIdx - 1 + endLineBump);
                    CubeDraw cubes = getCubeDrawNumberAndColour(drawLabel);
                    lastSpaceIdx = i + 1;

                    if (cubes.colour == "red" && cubes.number > redMin) {
                        redMin = cubes.number;
                    } if (cubes.colour == "green" && cubes.number > greeMin) {
                        greeMin = cubes.number;
                    } else if (cubes.colour == "blue" && cubes.number > blueMin) {
                        blueMin = cubes.number;
                    }
                }
            }

            sum += redMin * greeMin * blueMin;

        }
    } else {
        perror("Error opening file");
    }

    return sum;
}


int main() {
    int result_1 = sumOfGameIDs("data_real.txt");
    std::cout << "Total game IDs = " << result_1 << std::endl;
    int result_2 = sumOfGamePowers("data_real.txt");
    std::cout << "Total game powers = " << result_2 << std::endl;
    return 0;
}
