#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string partOne() {
    std::fstream inputFile;
    std::string buffer;

    inputFile.open("input.txt", std::ios::in);

    std::getline(inputFile, buffer);

    int stackCount = (buffer.size() + 1) / 4;
    std::vector<std::list<char>> stacks(stackCount);
    do {
        for (int i = 0; i < stackCount; i++) {
            char crane = buffer[4 * i + 1];
            if (crane != ' ') stacks[i].push_back(crane);
        }
        std::getline(inputFile, buffer);
    } while (buffer[1] != '1');

    std::getline(inputFile, buffer);

    char buf1[128];
    int move, from, to;
    while (inputFile >> buf1 >> move >> buf1 >> from >> buf1 >> to) {
        from--;
        to--;
        for (int i = 0; i < move; i++) {
            stacks[to].push_front(stacks[from].front());
            stacks[from].pop_front();
        }
    }

    inputFile.close();

    std::string topCranes;

    for (auto stack : stacks) {
        topCranes.push_back(stack.front());
    }

    return topCranes;
}

std::string partTwo() {
    std::fstream inputFile;
    std::string buffer;

    inputFile.open("input.txt", std::ios::in);

    std::getline(inputFile, buffer);

    int stackCount = (buffer.size() + 1) / 4;
    std::vector<std::list<char>> stacks(stackCount);
    do {
        for (int i = 0; i < stackCount; i++) {
            char crane = buffer[4 * i + 1];
            if (crane != ' ') stacks[i].push_back(crane);
        }
        std::getline(inputFile, buffer);
    } while (buffer[1] != '1');

    std::getline(inputFile, buffer);

    char buf1[128];
    int move, from, to;
    while (inputFile >> buf1 >> move >> buf1 >> from >> buf1 >> to) {
        from--;
        to--;

        auto fromEnd = stacks[from].begin();
        for (int i = 0; i < move; i++) fromEnd++;

        stacks[to].splice(stacks[to].begin(), stacks[from], stacks[from].begin(), fromEnd);
    }

    inputFile.close();

    std::string topCranes;

    for (auto stack : stacks) {
        topCranes.push_back(stack.front());
    }

    return topCranes;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
