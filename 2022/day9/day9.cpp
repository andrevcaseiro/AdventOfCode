#include <fstream>
#include <iostream>
#include <unordered_set>

union point {
    struct {
        int32_t x;
        int32_t y;
    } coords;

    int64_t repr;

    point() : repr(0) {}
};

void movePoint(point &p, char direction) {
    switch (direction) {
        case 'R':
            p.coords.x += 1;
            break;
        case 'L':
            p.coords.x -= 1;
            break;
        case 'U':
            p.coords.y += 1;
            break;
        case 'D':
            p.coords.y -= 1;
            break;
        default:
            break;
    }
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int partOne() {
    std::fstream inputFile;
    char direction;
    int repetitions;
    inputFile.open("input.txt", std::ios::in);

    std::unordered_set<int64_t> visitedPositions;
    point headPosition;
    point tailPosition;
    while (inputFile >> direction >> repetitions) {
        for (int i = 0; i < repetitions; i++) {
            movePoint(headPosition, direction);

            int xDif = headPosition.coords.x - tailPosition.coords.x;
            int yDif = headPosition.coords.y - tailPosition.coords.y;

            if (abs(xDif) > 1) {
                tailPosition.coords.x += xDif / 2;
                if (headPosition.coords.y != tailPosition.coords.y) {
                    tailPosition.coords.y += yDif;
                }
            } else if (abs(yDif) > 1) {
                tailPosition.coords.y += yDif / 2;
                if (headPosition.coords.x != tailPosition.coords.x) {
                    tailPosition.coords.x += xDif;
                }
            }

            visitedPositions.insert(tailPosition.repr);
        }
    }
    inputFile.close();

    return visitedPositions.size();
}

long partTwo() {
    std::fstream inputFile;
    char direction;
    int repetitions;
    inputFile.open("input.txt", std::ios::in);

    std::unordered_set<int64_t> visitedPositions;
    point positions[10];
    for (auto pos : positions) pos = point();

    while (inputFile >> direction >> repetitions) {
        for (int i = 0; i < repetitions; i++) {
            movePoint(positions[0], direction);

            for (int h = 0, t = 1; h < 9; h++, t++) {
                int xDif = positions[h].coords.x - positions[t].coords.x;
                int yDif = positions[h].coords.y - positions[t].coords.y;

                if (abs(xDif) > 1 || abs(yDif) > 1) {
                    positions[t].coords.x += sgn(xDif);
                    positions[t].coords.y += sgn(yDif);
                }
            }
            visitedPositions.insert(positions[9].repr);
        }
    }
    inputFile.close();

    return visitedPositions.size();
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
