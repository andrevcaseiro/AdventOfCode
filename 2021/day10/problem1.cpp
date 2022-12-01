#include <iostream>
#include <stack>

using namespace std;

int getScore(char c, stack<char>& s) {
    switch (c) {
        case '{':
        case '(':
        case '<':
        case '[':
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

int main() {
    string buff;
    int score;
    int totalScore = 0;

    while (getline(cin, buff)) {
        stack<char> s;
        for (char c : buff) {
            score = getScore(c, s);
            if (score > 0) break;
        }
        totalScore += score;
    }

    cout << totalScore << endl;

    return 0;
}