#include <fstream>
#include <iostream>
#include <cstring>

#define PACKET_MARKER_SIZE 4
#define MESSAGE_MARKER_SIZE 14

int partOne() {
    std::fstream inputFile;
    int buffer[PACKET_MARKER_SIZE];

    inputFile.open("input.txt", std::ios::in);

    int i = 0;
    int markerStart = 0;
    do {
        buffer[i % PACKET_MARKER_SIZE] = inputFile.get();
        if (buffer[i % PACKET_MARKER_SIZE] == EOF) return -1;

        for (int j = markerStart; j < i; j++) {
            if (buffer[i % PACKET_MARKER_SIZE] == buffer[j % PACKET_MARKER_SIZE]) {
                markerStart = j + 1;
                break;
            }
        }

        i++;
    } while (i - markerStart < PACKET_MARKER_SIZE);

    inputFile.close();

    return i;
}

int partTwo() {
    std::fstream inputFile;
    int lastSeen[128];

    std::memset(lastSeen, -1, sizeof(lastSeen));

    inputFile.open("input.txt", std::ios::in);

    int i = 0;
    int markerStart = 0;
    do {
        int c = inputFile.get();
        if (c == EOF) return -1;

        if(lastSeen[c] >= markerStart) markerStart = lastSeen[c] + 1;
        lastSeen[c] = i;

        i++;
    } while (i - markerStart < MESSAGE_MARKER_SIZE);

    inputFile.close();

    return i;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
