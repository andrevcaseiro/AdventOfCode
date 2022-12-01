#include <iostream>
#include <list>
#include <map>
#include <utility>

using namespace std;

template <class T, class Integer>
void insertOrAdd(map<T, Integer>* m, T key, Integer value) {
    auto it = m->find(key);

    if (it == m->end())
        m->insert(pair<T, Integer>(key, value));
    else
        it->second += value;
}

class Polymer {
    map<string, char> rules;
    string polymer;
    map<string, long>* pairFrequencies;

   public:
    Polymer(string str);
    void addRule(string str);
    void step();
    long profile();
};

Polymer::Polymer(string str) : polymer(str) {
    pairFrequencies = new map<string, long>();

    for (int i = 1; i < str.length(); i++) {
        string aux = str.substr(i - 1, 2);
        auto it = pairFrequencies->find(aux);
        insertOrAdd(pairFrequencies, aux, 1l);
    }
}

void Polymer::addRule(string str) { rules.insert(pair<string, char>(str.substr(0, 2), str[6])); }

void Polymer::step() {
    map<string, long>* newPairFrequencies = new map<string, long>();

    for (auto p : *pairFrequencies) {
        auto it = rules.find(p.first);
        if (it == rules.end()) {
            newPairFrequencies->insert(p);
        } else {
            char aux1[2] = {p.first[0], it->second};
            insertOrAdd(newPairFrequencies, string(aux1, 2), p.second);
            char aux2[2] = {it->second, p.first[1]};
            insertOrAdd(newPairFrequencies, string(aux2, 2), p.second);
        }
    }

    delete pairFrequencies;
    pairFrequencies = newPairFrequencies;

    return;
}

long Polymer::profile() {
    long frequencies['Z' - 'A' + 1];
    for (char c = 0; c <= 'Z' - 'A'; c++) {
        frequencies[c] = 0;
    }

    for (auto p : *pairFrequencies) {
        frequencies[p.first[0] - 'A'] += p.second;
        frequencies[p.first[1] - 'A'] += p.second;
    }

    frequencies[polymer[0] - 'A']++;
    frequencies[polymer[polymer.length() - 1] - 'A']++;
    for (char c = 0; c <= 'Z' - 'A'; c++) {
        frequencies[c] = frequencies[c] / 2;
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

    for (int i = 0; i < 40; i++) {
        pol.step();
    }

    cout << pol.profile() << endl;

    return 0;
}