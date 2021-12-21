#include <cctype>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Caves {
    struct node {
        bool visited;
        vector<map<string, node>::iterator> adjacents;

        node() : visited(false) {}
    };

    static const string start;
    static const string end;

    map<string, node> nodes;
    int transverse(map<string, node>::iterator start, map<string, node>::iterator end);

   public:
    Caves();
    void init();
    int pathCount();
};

const string Caves::start = "start";
const string Caves::end = "end";

Caves::Caves() {
    nodes.insert(pair<string, node>(start, node()));
    nodes.insert(pair<string, node>(end, node()));
}

void Caves::init() {
    string cave1, cave2;

    while (getline(cin, cave1, '-')) {
        getline(cin, cave2);

        auto it1 = nodes.insert(pair<string, node>(cave1, node())).first;
        auto it2 = nodes.insert(pair<string, node>(cave2, node())).first;

        it1->second.adjacents.push_back(it2);
        it2->second.adjacents.push_back(it1);
    }
}

int Caves::transverse(map<string, node>::iterator start, map<string, node>::iterator end) {
    int visited = 0;

    if (start == end) return 1;
    if (islower(start->first[0]) && start->second.visited) return 0;
    start->second.visited = true;

    for (auto it : start->second.adjacents) {
        visited += transverse(it, end);
    }

    start->second.visited = false;
    return visited;
}

int Caves::pathCount() {
    auto s = nodes.find(start);
    auto e = nodes.find(end);

    return transverse(s, e);
}

int main() {
    Caves caves;

    caves.init();

    cout << caves.pathCount() << endl;

    return 0;
}