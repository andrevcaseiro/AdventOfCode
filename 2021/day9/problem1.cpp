#include <iostream>
#include <vector>

using namespace std;

int main() {
    string buff;
    int sum = 0;
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

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int height = heightMap[i][j];
            if ((i == 0 || heightMap[i - 1][j] > height) && (i + 1 == len1 || heightMap[i + 1][j] > height) &&
                (j == 0 || heightMap[i][j - 1] > height) && (j + 1 == len2 || heightMap[i][j + 1] > height)) {
                sum += 1 + height;
            }
        }
    }

    cout << sum << endl;

    return 0;
}