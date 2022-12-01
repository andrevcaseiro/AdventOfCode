#include <iostream>
#include <string>

using namespace std;

int finalPosition() {
    int pos = 0, depth = 0, aim = 0;
    string instruction;
    int n;

    while (cin >> instruction) {
        cin >> n;

        if (instruction == "forward") {
            pos += n;
            depth += aim * n;
        } else if (instruction == "down") {
            aim += n;
        } else if (instruction == "up") {
            aim -= n;
        }
    }

    return pos * depth;
}

int main() {
    cout << finalPosition() << endl;

    return 0;
}