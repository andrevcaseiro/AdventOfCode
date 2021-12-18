#include <iostream>
#include <queue>

#define AVERAGE 3

using namespace std;

int countIncreased() {
    queue<int> q;
    int curr, timesIncreased = 0;

    for (int i = 0; i < AVERAGE; i++) {
        cin >> curr;
        q.push(curr);
    }
    
    while (cin >> curr) {
        if (curr > q.front()) timesIncreased++;
        q.pop();
        q.push(curr);
    }

    return timesIncreased;
}

int main() {
    cout << countIncreased() << endl;

    return 0;
}