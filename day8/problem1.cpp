#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    int count = 0;
    int i, l, r;

    while (getline(cin, str)) {
        l = 61;
        for (i = 0; i < 4; i++) {
            if(i == 3) r = str.size();
            else r = str.find(" ", l);
            
            switch (r - l) {
                case 2 ... 4:
                case 7:
                    count++;
            }
            l = r + 1;
        }
    }

    cout << count << endl;

    return 0;
}