#include <iostream>
#include <vector>

using namespace std;

class OctopusGrid {
    vector<vector<int>> energies;
    long flashes;

    void energise(int i, int j);

   public:
    OctopusGrid() : flashes(0) {}
    void init();
    void step();
    long getFlashes() { return flashes; }
};

void OctopusGrid::energise(int i, int j) {
    if (i < 0 || i >= energies.size() || j < 0 || j >= energies[0].size()) return;

    energies[i][j]++;
    if (energies[i][j] == 10) {
        flashes++;
        energise(i - 1, j - 1);
        energise(i - 1, j);
        energise(i - 1, j + 1);
        energise(i, j + 1);
        energise(i + 1, j + 1);
        energise(i + 1, j);
        energise(i + 1, j - 1);
        energise(i, j - 1);
    }
}

void OctopusGrid::init() {
    string buff;

    while (getline(cin, buff)) {
        vector<int> vec;
        for (char c : buff) {
            vec.push_back(atoi(&c));
        }
        energies.push_back(vec);
    }
}

void OctopusGrid::step() {
    int i, j;
    for (i = 0; i < energies.size(); i++) {
        for (j = 0; j < energies[0].size(); j++) {
            energise(i, j);
        }
    }
    for (i = 0; i < energies.size(); i++) {
        for (j = 0; j < energies[0].size(); j++) {
            if (energies[i][j] > 9) energies[i][j] = 0;
        }
    }
}

int main() {
    OctopusGrid grid;

    grid.init();

    for (int i = 0; i < 100; i++) {
        grid.step();
    }

    cout << grid.getFlashes() << endl;

    return 0;
}