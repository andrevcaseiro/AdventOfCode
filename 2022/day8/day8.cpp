#include <cstring>
#include <fstream>
#include <iostream>

long partOne() {
    std::fstream inputFile;
    char buffer[128];
    inputFile.open("input.txt", std::ios::in);

    inputFile.getline(buffer, sizeof(buffer));
    int mapSize = inputFile.gcount();
    char map[mapSize][mapSize];
    std::strncpy(map[0], buffer, mapSize);

    for (int i = 1; i < mapSize; i++) {
        inputFile.getline(map[i], mapSize);
    }
    mapSize -= 1;

    inputFile.close();

    int visibleTrees = 0;
    for (int i = 0; i < mapSize; i++) {
        char tallest = 0;
        int lastSeen = -1;
        for (int j = 0; j < mapSize; j++) {
            if (map[i][j] > tallest) {
                tallest = map[i][j];
                map[i][j] |= 0b10000000;
                lastSeen = j;
                visibleTrees++;
            }
        }

        tallest = 0;
        for (int j = mapSize - 1; j > lastSeen; j--) {
            if (map[i][j] > tallest) {
                tallest = map[i][j];
                map[i][j] |= 0b10000000;
                visibleTrees++;
            }
        }
    }
    for (int i = 0; i < mapSize; i++) {
        char tallest = 0;
        int lastSeen = -1;
        for (int j = 0; j < mapSize; j++) {
            if ((map[j][i] & 0b01111111) > tallest) {
                tallest = (map[j][i] & 0b01111111);
                lastSeen = j;
                if ((map[j][i] & 0b10000000) == 0) {
                    visibleTrees++;
                    map[j][i] |= 0b10000000;
                }
            }
        }

        tallest = 0;
        for (int j = mapSize - 1; j > lastSeen; j--) {
            if ((map[j][i] & 0b01111111) > tallest) {
                tallest = (map[j][i] & 0b01111111);
                if ((map[j][i] & 0b10000000) == 0) {
                    visibleTrees++;
                    map[j][i] |= 0b10000000;
                }
            }
        }
    }

    return visibleTrees;
}

long partTwo() {
    std::fstream inputFile;
    char buffer[128];
    inputFile.open("input.txt", std::ios::in);

    inputFile.getline(buffer, sizeof(buffer));
    int mapSize = inputFile.gcount();
    char map[mapSize][mapSize];
    std::strncpy(map[0], buffer, mapSize);

    for (int i = 1; i < mapSize; i++) {
        inputFile.getline(map[i], mapSize);
    }
    mapSize -= 1;

    inputFile.close();

    char viewDistanceArray[10];
    char *viewDistance = viewDistanceArray - '0';
    int scenicScore[mapSize][mapSize];
    for (int i = 0; i < mapSize; i++) {
        memset(viewDistanceArray, 0, sizeof(viewDistanceArray));
        for (int j = 0; j < mapSize; j++) {
            scenicScore[i][j] = j - viewDistance[map[i][j]];
            for (int k = map[i][j]; k >= 0; k--) viewDistance[k] = j;
        }

        memset(viewDistanceArray, mapSize - 1, sizeof(viewDistanceArray));
        for (int j = mapSize - 1; j >= 0; j--) {
            scenicScore[i][j] *= viewDistance[map[i][j]] - j;
            for (int k = map[i][j]; k >= 0; k--) viewDistance[k] = j;
        }
    }
    for (int i = 0; i < mapSize; i++) {
        memset(viewDistanceArray, 0, sizeof(viewDistanceArray));
        for (int j = 0; j < mapSize; j++) {
            scenicScore[j][i] *= j - viewDistance[map[j][i]];
            for (int k = map[j][i]; k >= 0; k--) viewDistance[k] = j;
        }

        memset(viewDistanceArray, mapSize - 1, sizeof(viewDistanceArray));
        for (int j = mapSize - 1; j >= 0; j--) {
            scenicScore[j][i] *= viewDistance[map[j][i]] - j;
            for (int k = map[j][i]; k >= 0; k--) viewDistance[k] = j;
        }
    }

    int maxScenicScore = 0;
    for(auto& row: scenicScore) {
        for(auto& score : row) {
            if(score > maxScenicScore) maxScenicScore = score;
        }
    }

    return maxScenicScore;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
