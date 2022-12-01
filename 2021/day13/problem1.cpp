#include <iostream>
#include <set>
#include <sstream>

using namespace std;

struct Dot {
    int x, y;

    Dot(int x, int y) : x(x), y(y) {}

    bool foldX(int x);
    bool foldY(int y);
};

class Comparator {
   public:
    bool operator()(Dot* d1, Dot* d2) { return d1->x < d2->x || (d1->x == d2->x && d1->y < d2->y); }
};

bool Dot::foldX(int x) {
    if (this->x == x)
        return false;
    else if (this->x > x) {
        this->x = 2*x - this->x;
    }
    return true;
}
bool Dot::foldY(int y) {
    if (this->y == y)
        return false;
    else if (this->y > y) {
        this->y = 2*y - this->y;
    }
    return true;
}

int main() {
    int x, y;
    string buff;
    char c;
    set<Dot*, Comparator> s;

    getline(cin, buff);
    while (buff.size() > 0) {
        istringstream sstream(buff);
        sstream >> x;
        sstream >> c;
        sstream >> y;
        s.insert(new Dot(x, y));
        getline(cin, buff);
    }

    getline(cin, buff, '=');
    if (buff[11] == 'x') {
        cin >> x;
        auto it = s.begin();
        while (it != s.end()) {
            auto aux = it;
            Dot* dot = *it;

            it++;
            s.erase(aux);
            if (dot->foldX(x)) s.insert(it, dot);
        }
    }
    if (buff[11] == 'y') {
        cin >> y;
        auto it = s.begin();
        while (it != s.end()) {
            auto aux = it;
            Dot* dot = *it;

            it++;
            s.erase(aux);
            if (dot->foldY(y)) s.insert(it, dot);
        }
    }

    while(getline(cin, buff));

    cout << s.size() << endl;

    return 0;
}