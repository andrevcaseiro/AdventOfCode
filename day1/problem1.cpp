#include <iostream>

using namespace std;

/**
 * @brief Reads all numbers from stdin and counts the number of times
 * a number was higher than the previous
 * 
 * @return int number of times a number was higher than the previous
 */
int countIncreased() {
    int prev, curr;
    int timesIncreased = 0;

    cin >> prev;
    while (cin >> curr) {
        if (curr > prev) timesIncreased++;
        prev = curr;
    }

    return timesIncreased;
}

int main() {
    cout << countIncreased() << endl;

    return 0;
}