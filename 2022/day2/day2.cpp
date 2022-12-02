#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <queue>

int partOne() {
    std::fstream inputFile;
    char buffer[128];
    int totalScore = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, 128)) {
        int elfShape = buffer[0] - 'A';
        int myShape = buffer[2] - 'X';
        int outcome;

        if (elfShape == myShape)
            outcome = 3;
        else if (elfShape == (myShape + 1) % 3)
            outcome = 0;
        else
            outcome = 6;

        totalScore += outcome + myShape + 1;
    }

    inputFile.close();

    return totalScore;
}

int partTwo() {
    std::fstream inputFile;
    char buffer[128];
    int totalScore = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, 128)) {
        int elfShape = buffer[0] - 'A';
        int outcome = buffer[2] - 'X';
        int myShape = (elfShape + 2 + outcome) % 3;

        totalScore += 3 * outcome + myShape + 1;
    }

    inputFile.close();

    return totalScore;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
