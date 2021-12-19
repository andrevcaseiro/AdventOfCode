#include <iostream>

using namespace std;

int main() {
    int i, j, temp;
    int fishCount[9] = {0};

    do {
        cin >> temp;
        fishCount[temp]++;
    } while(getchar() == ',');

    for (i = 0; i <= 80; i++) {
        temp = fishCount[0];

        for(j = 0; j < 8; j++) {
            fishCount[j] = fishCount[j+1];
        }

        fishCount[8] = temp;
        fishCount[6] += temp;

    }

    temp = 0;
    for(i = 0; i < 8; i++) {
        temp += fishCount[i];
    }

    cout << temp << endl;

    return 0;
}