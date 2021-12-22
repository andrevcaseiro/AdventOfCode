#include <iostream>
#include <list>
#include <map>

using namespace std;

class Polymer {
    map<string, char> rules;
    list<char> polymer;

   public:
    Polymer(string str);
    void addRule(string str);
    void step();
    int profile();
};

Polymer::Polymer(string str) {
    for (char c : str) polymer.push_back(c);
}

void Polymer::addRule(string str) { rules.insert(pair<string, char>(str.substr(0, 2), str[6])); }

void Polymer::step() {
    auto it = polymer.begin();
    auto aux = it;
    aux++;

    while (aux != polymer.end()) {
        char temp[2] = {*it, *aux};
        auto rule = rules.find(string(temp, 2));

        if (rule != rules.end()) polymer.insert(aux, rule->second);

        it = aux;
        aux++;
    }
}

int Polymer::profile() {
    long frequencies['Z' - 'A' + 1];
    for (char c = 0; c <= 'Z' - 'A'; c++) {
        frequencies[c] = 0;
    }

    for (char c : polymer) {
        frequencies[c - 'A']++;
    }

    long min = frequencies[0];
    long max = frequencies[0];
    for (char c = 0; c <= 'Z' - 'A'; c++) {
        if (frequencies[c] > max)
            max = frequencies[c];
        else if (frequencies[c] != 0 && (frequencies[c] < min || min == 0))
            min = frequencies[c];
    }

    return max - min;
}

int main() {
    string buff;

    getline(cin, buff);
    Polymer pol(buff);

    getline(cin, buff);
    while (getline(cin, buff)) {
        pol.addRule(buff);
    }

    for (int i = 0; i < 10; i++) {
        pol.step();
    }

    cout << pol.profile() << endl;

    return 0;
}