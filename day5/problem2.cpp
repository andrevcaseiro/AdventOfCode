#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Line {
    int x1, x2, y1, y2;

    Line(int x1, int y1, int x2, int y2) {
        this->y1 = min(y1, y2);
        this->y2 = max(y1, y2);
        if (y1 == y2) {
            this->x1 = min(x1, x2);
            this->x2 = max(x1, x2);
        } else if (y1 < y2) {
            this->x1 = x1;
            this->x2 = x2;
        } else {
            this->x1 = x2;
            this->x2 = x1;
        }
    }
};

class Compare {
   public:
    bool operator()(Line* l1, Line* l2) {
        return l1->y1 > l2->y1 || (l1->y1 == l2->y1 && l1->x1 > l2->x1);
    }
};

priority_queue<Line*, vector<Line*>, Compare>* readLines() {
    int x1, x2, y1, y2;
    auto q = new priority_queue<Line*, vector<Line*>, Compare>();

    while (cin >> x1) {
        getchar();
        cin >> y1;
        getchar();
        getchar();
        getchar();
        getchar();
        cin >> x2;
        getchar();
        cin >> y2;

        q->push(new Line(x1, y1, x2, y2));
    }

    return q;
}

int countIntersections(priority_queue<Line*, vector<Line*>, Compare>* q) {
    Line* l;
    int x1 = -1, x2 = -1, y = -1;
    int xx1, xx2;
    int count = 0;

    while (q->size() > 0) {
        l = q->top();
        q->pop();

        if (l->y1 > y) {
            // l is on a new line, reset interval
            y = l->y1;
            x1 = -1;
            x2 = -1;
        }
        if (l->x1 != l->x2 && l->y1 != l->y2) {
            // l is diagonal, split in two

            xx1 = l->x1;
            l->y1++;
            l->x1 = l->x1 > l->x2 ? l->x1 -1 : l->x1 + 1;
            q->push(l);
            l = new Line(xx1, y, xx1, y);
        }
        if (l->x2 < x1) {
            // l has already been included, do nothing
        } else if (l->x1 > x2) {
            // l doesnt intersect, update interval
            x1 = l->x1;
            x2 = l->x2;
        } else {
            // l intersects, update count
            xx1 = max(l->x1, x1);
            xx2 = min(l->x2, x2) + 1;

            count += xx2 - xx1;

            x1 = xx2;
            x2 = max(l->x2, x2);
        }

        if (l->y2 > y) {
            l->y1++;
            q->push(l);
        }
    }

    return count;
}

int main() {
    priority_queue<Line*, vector<Line*>, Compare>* q = readLines();

    cout << countIntersections(q) << endl;

    return 0;
}