#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Comparator {
   public:
    bool operator()(string s1, string s2) {
        return s1.size() < s2.size();
    }
};

class sevenBitDisplay {
    char segments[7];

   public:
    sevenBitDisplay(string sample[]);

    int decode(string str);
};

sevenBitDisplay::sevenBitDisplay(string sample[]) {
    char display = 0b0000000;
    sort(sample, sample + 10, Comparator());

    for (int i = 0; i < 7; i++) {
        segments[i] = 0;
    }

    // Number 1 : right segments
    for (char c : sample[0]) {
        if (sample[6].find(c) == string::npos || sample[7].find(c) == string::npos || sample[8].find(c) == string::npos) {
            segments[c - 'a'] = 0b0010000;
        } else {
            segments[c - 'a'] = 0b0000001;
        }
    }

    // Number 7 : top segment
    for(char c: sample[1]) {
        if(sample[0].find(c) == string::npos) {
            segments[c - 'a'] = 0b0100000;
        }
    }

    // Number 4 : middle and top left segments
    for(char c: sample[2]) {
        if(sample[0].find(c) == string::npos) {
            if (sample[3].find(c) == string::npos || sample[4].find(c) == string::npos || sample[5].find(c) == string::npos) {
                segments[c - 'a'] = 0b1000000;
            } else {
                segments[c - 'a'] = 0b0001000;
            }
        }
    }

    for (char i = 0; i < 7; i++) {
        if (segments[i] == 0) {
            char c = i + 'a';
            if (sample[3].find(c) == string::npos || sample[4].find(c) == string::npos || sample[5].find(c) == string::npos) {
                segments[i] = 0b0000100;
            } else {
                segments[i] = 0b0000010;
            }
        }
    }
}

int sevenBitDisplay::decode(string str) {
    char display = 0b0000000;
    for (char c : str) {
        display = display | segments[c - 'a'];
    }

    switch (display) {
        case 0b1110111:
            return 0;
        case 0b0010001:
            return 1;
        case 0b0111110:
            return 2;
        case 0b0111011:
            return 3;
        case 0b1011001:
            return 4;
        case 0b1101011:
            return 5;
        case 0b1101111:
            return 6;
        case 0b0110001:
            return 7;
        case 0b1111111:
            return 8;
        case 0b1111011:
            return 9;
        default:
            return -1;
    }
}

int main() {
    string str[15];
    int count = 0;
    int i, aux;

    while (cin >> str[0]) {
        for (i = 1; i < 15; i++) {
            cin >> str[i];
        }

        sevenBitDisplay display = sevenBitDisplay(str);

        aux = 0;
        for (i = 11; i < 15; i++) {
            aux = aux * 10;
            aux += display.decode(str[i]);
        }
        count += aux;
    }

    cout << count << endl;

    return 0;
}