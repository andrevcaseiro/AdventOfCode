#include <iostream>
#include <list>
#include <sstream>

using namespace std;

class Bingo {
    class Board {
        int numbers[5][5];
        int rowSum[5];
        int collumnSum[5];

        int score(int lastNumber);

       public:
        Board();
        void readBoard();
        int markNumber(int number);
    };

    list<Board*> boards;

   public:
    void addBoard();
    int markNumber(int number);
};

Bingo::Board::Board() {
    for (int i = 0; i < 5; i++) {
        rowSum[i] = 0;
        collumnSum[i] = 0;
    }
}

void Bingo::Board::readBoard() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> numbers[i][j];
        }
    }
}

int Bingo::Board::markNumber(int number) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (numbers[i][j] == number) {
                numbers[i][j] = -1;
                if (++rowSum[i] == 5 || ++collumnSum[j] == 5) {
                    return score(number);
                }
            }
        }
    }

    return 0;
}

int Bingo::Board::score(int lastNumber) {
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (numbers[i][j] != -1) {
                sum += numbers[i][j];
            }
        }
    }

    return sum * lastNumber;
}

void Bingo::addBoard() {
    Board* board = new Board();
    board->readBoard();
    boards.push_back(board);
}

int Bingo::markNumber(int number) {
    int score;
    for (Board* board : boards) {
        score = board->markNumber(number);
        if (score > 0) {
            return score;
        }
    }

    return 0;
}

int playBingo() {
    string str;
    int number;
    int score;
    Bingo bingo;

    getline(cin, str);

    while (getchar() == '\n') {
        bingo.addBoard();
        getchar();
    }

    istringstream sstream(str);
    char c;
    do {
        sstream >> number;
        score = bingo.markNumber(number);
        if (score > 0) {
            return score;
        }
        sstream >> c;
    } while (c = ',');

    return -1;
}

int main() {
    cout << playBingo() << endl;

    return 0;
}