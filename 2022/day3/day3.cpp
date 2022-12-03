#include <cstring>
#include <fstream>
#include <iostream>

int getPriority(char item) {
    if (item >= 'a' && item <= 'z') {
        return item - 'a' + 1;
    }

    return item - 'A' + 27;
}

int partOne() {
    std::fstream inputFile;
    char buffer[128];
    char items[26 * 2 + 1];
    int totalPriority = 0;
    int rsPriority = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, 128)) {
        int i;
        int rsItemCount = inputFile.gcount() - 1;
        std::memset(items, '\0', sizeof(items));

        for (i = 0; i < rsItemCount / 2; i++) {
            items[getPriority(buffer[i])] = 1;
        }

        while (i < rsItemCount) {
            rsPriority = getPriority(buffer[i]);
            if (items[rsPriority] == 1) break;
            i++;
        }

        totalPriority += rsPriority;
    }

    inputFile.close();

    return totalPriority;
}

int partTwo() {
    std::fstream inputFile;
    char buffer[128];
    char items[26 * 2 + 1];
    int totalPriority = 0;
    int rsPriority = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, sizeof(buffer))) {
        int i;
        std::memset(items, '\0', sizeof(items));

        for (i = 0; i < 3; i++) {
            if (i != 0) inputFile.getline(buffer, sizeof(buffer));
            int rsItemCount = inputFile.gcount() - 1;

            for (int j = 0; j < rsItemCount; j++) {
                rsPriority = getPriority(buffer[j]);
                if (items[rsPriority] == i) items[rsPriority] = i + 1;
            }
        }

        for (rsPriority = 1; rsPriority < sizeof(items); rsPriority++) {
            if (items[rsPriority] == 3) break;
        }

        totalPriority += rsPriority;
    }

    inputFile.close();

    return totalPriority;
}

int main() {
    std::cout << 5 / 2 << std::endl;
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
