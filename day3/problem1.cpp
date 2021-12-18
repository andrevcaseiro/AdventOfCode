#include <iostream>
#include <vector>

using namespace std;

int powerConsumption() {
    int gamma = 0, epsilon = 0;
    int lines = 0;
    string str;

    getline(cin, str);
    vector<int> sums(str.size(), 0);

    do {
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '1') sums[i]++;
        }
        lines++;
    } while (getline(cin, str));

    for (int sum : sums) {
        gamma = gamma * 2;
        epsilon = epsilon * 2;

        if (2 * sum > lines)
            gamma = gamma + 1;
        else
            epsilon = epsilon + 1;
    }

    return gamma * epsilon;
}

int main() {
    cout << powerConsumption() << endl;

    return 0;
}