#include <iostream>
#include <iterator>
#include <set>
#include <stack>

using namespace std;

int corruptScore(char c, stack<char>& s) {
    switch (c) {
        case '(':
        case '[':
        case '{':
        case '<':
            s.push(c);
            break;
        case ')':
            if (s.top() != '(') return 3;
            s.pop();
            break;
        case ']':
            if (s.top() != '[') return 57;
            s.pop();
            break;
        case '}':
            if (s.top() != '{') return 1197;
            s.pop();
            break;
        case '>':
            if (s.top() != '<') return 25137;
            s.pop();
            break;
        default:
            break;
    }
    return 0;
}

long stackScore(stack<char>& s) {
    char c;
    long score = 0;

    while (s.size() != 0) {
        score *= 5;
        c = s.top();
        switch (c) {
            case '(':
                score += 1;
                break;
            case '[':
                score += 2;
                break;
            case '{':
                score += 3;
                break;
            case '<':
                score += 4;
                break;
            default:
                break;
        }
        s.pop();
    }

    return score;
}

int main() {
    string buff;
    int score;
    multiset<long> scores;

corrupted:
    while (getline(cin, buff)) {
        stack<char> s;
        for (char c : buff) {
            score = corruptScore(c, s);
            if (score > 0) goto corrupted;
        }
        scores.insert(stackScore(s));
    }

    auto it = scores.begin();
    advance(it, scores.size() / 2);

    cout << *it << endl;

    return 0;
}