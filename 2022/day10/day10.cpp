#include <fstream>
#include <iostream>
#include <unordered_set>

void tick1(int &cycle, int reg, int &signalStrengthSum) {
    cycle++;

    if ((cycle + 20) % 40 == 0) {
        signalStrengthSum += cycle * reg;
    }
}

int partOne() {
    std::fstream inputFile;
    char buffer[128];
    int value;
    inputFile.open("input.txt", std::ios::in);

    int cycle = 1;
    int reg = 1;
    int signalStrengthSum = 0;
    while (inputFile.getline(buffer, sizeof(buffer))) {
        switch (buffer[0]) {
            case 'n':
                tick1(cycle, reg, signalStrengthSum);
                break;
            case 'a':
                value = atoi(buffer + 5);
                tick1(cycle, reg, signalStrengthSum);
                reg += value;
                tick1(cycle, reg, signalStrengthSum);
                break;
            default:
                break;
        }
    }

    inputFile.close();

    return signalStrengthSum;
}

void tick2(int &cycle, int reg, char crt[]) {
    int crtPos = cycle - 1;
    if (reg - 1 <= crtPos % 40 && crtPos % 40 <= reg + 1) {
        crt[crtPos] = '#';
    } else {
        crt[crtPos] = '.';
    }
    cycle++;
}

std::string partTwo() {
    std::fstream inputFile;
    char buffer[128];
    char crt[240];
    int value;
    inputFile.open("input.txt", std::ios::in);

    int cycle = 1;
    int reg = 1;
    while (inputFile.getline(buffer, sizeof(buffer))) {
        switch (buffer[0]) {
            case 'n':
                tick2(cycle, reg, crt);
                break;
            case 'a':
                value = atoi(buffer + 5);
                tick2(cycle, reg, crt);
                tick2(cycle, reg, crt);
                reg += value;
                break;
            default:
                break;
        }
    }

    inputFile.close();

    std::string screen;
     for (int i = 0; i < 6; i++) {
         screen += std::string(crt + 40 * i, 40) + "\n";
     }

    return screen;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two:\n" << partTwo() << std::endl;
}
