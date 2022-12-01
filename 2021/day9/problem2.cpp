#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Basins {
    vector<int> vec;

   public:
    int newBasin() {
        vec.push_back(1);
        return vec.size() - 1;
    }
    int addToBasin(int b) {
        if (b == -1) {
            return newBasin();
        }
        while (vec[b] <= 0) {
            b = -vec[b];
        }
        vec[b]++;
        return b;
    }
    int addToBasin(int b1, int b2) {
        if (b1 == -1) {
            return addToBasin(b2);
        }
        if (b2 == -1) {
            return addToBasin(b1);
        }
        while (vec[b1] <= 0) {
            b1 = -vec[b1];
        }
        while (vec[b2] <= 0) {
            b2 = -vec[b2];
        }
        if (b1 == b2) {
            vec[b1]++;
        } else if (b1 < b2) {
            vec[b1] += vec[b2] + 1;
            vec[b2] = -b1;
        } else {
            vec[b2] += vec[b1] + 1;
            vec[b1] = -b2;
            return b2;
        }
        return b1;
    }

    int product() {
        sort(vec.begin(), vec.end(), greater<int>());
        return vec[0] * vec[1] * vec[2];
    }
};

int main() {
    string buff;
    vector<vector<int>> heightMap;

    while (getline(cin, buff)) {
        vector<int> vec;
        for (char c : buff) {
            vec.push_back(atoi(&c));
        }
        heightMap.push_back(vec);
    }

    int len1 = heightMap.size();
    int len2 = heightMap[0].size();
    Basins basins;
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (heightMap[i][j] == 9) {
                heightMap[i][j] = -1;

            } else if ((i == 0) && (j == 0)) {
                heightMap[i][j] = basins.newBasin();
            } else {
                if (i == 0) {
                    heightMap[i][j] = basins.addToBasin(heightMap[i][j - 1]);
                } else if (j == 0) {
                    heightMap[i][j] = basins.addToBasin(heightMap[i - 1][j]);
                } else {
                    heightMap[i][j] = basins.addToBasin(heightMap[i][j - 1], heightMap[i - 1][j]);
                }
            }
            if (heightMap[i][j] > 1000)
                i++;
        }
    }

    cout << basins.product() << endl;

    return 0;
}