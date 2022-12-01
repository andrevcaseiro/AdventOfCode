#include <iostream>
#include <string>

using namespace std;

int finalPosition() {
    int pos = 0, depth = 0;
    string instruction;
    int n;

    while (cin >> instruction) {
        cin >> n;

        if (instruction == "forward") {
            pos += n;
        } else if (instruction == "down") {
            depth += n;
        } else if (instruction == "up") {
            depth -= n;
        }
    }

    return pos * depth;
}

int main() {
    cout << finalPosition() << endl;

    return 0;
}