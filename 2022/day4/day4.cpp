#include <algorithm>
#include <fstream>
#include <iostream>

int partOne() {
    std::fstream inputFile;
    int elf1FirstSection, elf1LastSection, elf2FirstSection, elf2LastSection;
    char separator;
    int totalFullyContained = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile >> elf1FirstSection >> separator >> elf1LastSection >> separator >>
           elf2FirstSection >> separator >> elf2LastSection) {
        if ((elf1FirstSection <= elf2FirstSection && elf1LastSection >= elf2LastSection) ||
            (elf2FirstSection <= elf1FirstSection && elf2LastSection >= elf1LastSection)) {
            totalFullyContained++;
        }
    }

    inputFile.close();

    return totalFullyContained;
}

int partTwo() {
    std::fstream inputFile;
    int elf1FirstSection, elf1LastSection, elf2FirstSection, elf2LastSection;
    char separator;
    int totalFullyContained = 0;

    inputFile.open("input.txt", std::ios::in);

    while (inputFile >> elf1FirstSection >> separator >> elf1LastSection >> separator >>
           elf2FirstSection >> separator >> elf2LastSection) {
        if (std::min(elf1LastSection, elf2LastSection) >=
            std::max(elf1FirstSection, elf2FirstSection)) {
            totalFullyContained++;
        }
    }

    inputFile.close();

    return totalFullyContained;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
