#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <queue>

int partOne() {
    std::fstream inputFile;
    char buffer[128];
    int maxCalories = 0;
    int elfCalories = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, 128)) {
        if (buffer[0] != '\0') {
            elfCalories += std::atoi(buffer);
        } else {
            if (elfCalories > maxCalories) {
                maxCalories = elfCalories;
            }
            elfCalories = 0;
        }
    }

    inputFile.close();

    return maxCalories;
}

int partTwo() {
    std::fstream inputFile;
    char buffer[128];
    std::priority_queue<int, std::vector<int>, std::greater<int>> maxCalories;
    int size, sum;
    int elfCalories = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, 128)) {
        if (buffer[0] != '\0') {
            elfCalories += std::atoi(buffer);
        } else {
            if (maxCalories.size() < 3) {
                maxCalories.push(elfCalories);
            } else if (elfCalories > maxCalories.top()) {
                maxCalories.pop();
                maxCalories.push(elfCalories);
            }
            elfCalories = 0;
        }
    }

    inputFile.close();

    sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += maxCalories.top();
        maxCalories.pop();
    }

    return sum;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
