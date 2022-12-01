#include <iostream>

#define TABLE_SIZE 2000

using namespace std;

int main() {
    int i, temp, cost;
    int max = 0;
    int positions[TABLE_SIZE] = {0};
    int costs[TABLE_SIZE] = {0};

    do {
        cin >> temp;
        positions[temp]++;
        if (temp > max) max = temp;
    } while (getchar() == ',');

    max++;
    cost = 0;
    temp = 0;
    for (i = 0; i < max; i++) {
        costs[i] = cost;
        temp += positions[i];
        cost += temp;
    }

    cost = 0;
    temp = 0;
    for (i = max - 1; i >= 0; i--) {
        costs[i] += cost;
        temp += positions[i];
        cost += temp;
    }

    temp = costs[0];
    for (i = 1; i < max; i++) {
        if (costs[i] < temp) temp = costs[i];
    }

    cout << temp << endl;

    return 0;
}