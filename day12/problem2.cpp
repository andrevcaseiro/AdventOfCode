#include <cctype>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Caves {
    struct node {
        bool visited;
        vector<map<string, node>::iterator>* adjacents;

        node() : visited(false) { adjacents = new vector<map<string, node>::iterator>(); }
    };

    static const string start;
    static const string end;

    map<string, node>::iterator itStart;
    map<string, node>::iterator itEnd;

    map<string, node> nodes;
    int transverse(map<string, node>::iterator start, map<string, node>::iterator end,
                   bool canRevisit);

   public:
    Caves();
    void init();
    int pathCount();
};

const string Caves::start = "start";
const string Caves::end = "end";

Caves::Caves() {
    itStart = nodes.insert(pair<string, node>(start, node())).first;
    itEnd = nodes.insert(pair<string, node>(end, node())).first;
}

void Caves::init() {
    string cave1, cave2;

    while (getline(cin, cave1, '-')) {
        getline(cin, cave2);

        auto it1 = nodes.insert(pair<string, node>(cave1, node())).first;
        auto it2 = nodes.insert(pair<string, node>(cave2, node())).first;

        it1->second.adjacents->push_back(it2);
        it2->second.adjacents->push_back(it1);
    }
}

int Caves::transverse(map<string, node>::iterator start, map<string, node>::iterator end,
                      bool canRevisit) {
    int visited = 0;
    bool resetVisited = true;

    if (start == end) {
        // cout << start->first << "{}" << endl;
        return 1;
    }
    if (islower(start->first[0]) && start->second.visited) {
        if (canRevisit && start != itStart) {
            resetVisited = false;
            canRevisit = false;
        } else {
            // cout << start->first << "{}" << endl;
            return 0;
        }
    }
    start->second.visited = true;

    // cout << start->first << "{" << endl;

    for (auto it : *start->second.adjacents) {
        visited += transverse(it, end, canRevisit);
    }

    // cout << "}" << endl;

    if (resetVisited) start->second.visited = false;
    return visited;
}

int Caves::pathCount() { return transverse(itStart, itEnd, true); }

int main() {
    Caves caves;

    caves.init();

    cout << caves.pathCount() << endl;

    return 0;
}
