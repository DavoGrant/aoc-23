#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


class Animal {
    public:
        int m_currentRowIdx;
        int m_currentColIdx;
        int m_numberOfStepsTaken;

        Animal(std::vector<std::vector<char>> sketchMap) {
            m_sketchMap = sketchMap;
            m_numberOfStepsTaken = 0;
            m_nextDirection = "none";
        }

        void runAroundLoop(int startRowIdx, int startColIdx, std::string startDirection) {
            m_currentRowIdx = startRowIdx;
            m_currentColIdx = startColIdx;
            m_nextDirection = startDirection;
            this->step();
            while (m_sketchMap[m_currentRowIdx][m_currentColIdx] != 'S') {
                this->step();
            }
        }

    protected:
        std::vector<std::vector<char>> m_sketchMap;
        std::string m_nextDirection;

        void step() {

            if (m_nextDirection == "north") {
                m_currentRowIdx -= 1;
                if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == '7') {
                    m_nextDirection = "west";
                } else if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'F') {
                    m_nextDirection = "east";
                }
            } else if (m_nextDirection == "east") {
                m_currentColIdx += 1;
                if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == '7') {
                    m_nextDirection = "south";
                } else if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'J') {
                    m_nextDirection = "north";
                }
            } else if (m_nextDirection == "south") {
                m_currentRowIdx += 1;
                if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'L') {
                    m_nextDirection = "east";
                } else if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'J') {
                    m_nextDirection = "west";
                }
            } else if (m_nextDirection == "west") {
                m_currentColIdx -= 1;
                if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'L') {
                    m_nextDirection = "north";
                } else if (m_sketchMap[m_currentRowIdx][m_currentColIdx] == 'F') {
                    m_nextDirection = "south";
                }
            }
            m_numberOfStepsTaken += 1;
        }
};


int countSteps(const std::string& file_name, std::string startDirection, bool printSketch) {

    std::ifstream f (file_name);
    if (!f.is_open()) {
        perror("Error opening file");
    }

    int startRowIdx = 0;
    int startColIdx = 0;
    std::vector<std::vector<char> > sketchMap;
    std::string line;
    int rowIdx = 0;
    while (std::getline(f, line)) {
        std::vector<char> row;
        for (std::string::size_type i = 0; i < line.size(); i++) {
            char pipePiece = line[i];
            row.push_back(pipePiece);
            if (pipePiece == 'S') {
                startRowIdx = rowIdx;
                startColIdx = i;
            }
        }
        sketchMap.push_back(row);
        rowIdx += 1;
    }

    if (printSketch) {
        for (std::vector<char> &row : sketchMap) {
            for (char &c : row) std::cout << c << ' ';
            std::cout << '\n';
        }
        std::cout << "Starting at row index " << startRowIdx;
        std::cout << " and col index " << startColIdx << std::endl;
    }

    Animal XmasSquirrel(sketchMap);
    XmasSquirrel.runAroundLoop(startRowIdx, startColIdx, startDirection);

    return XmasSquirrel.m_numberOfStepsTaken;
}


int main() {
    int result = countSteps("data_real.txt", "south", false);
    std::cout << "Total steps to farthest point = " << result / 2 << std::endl;
    return 0;
}
