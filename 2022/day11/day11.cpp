#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

enum operation {
    MULTIPLY,
    ADD,
};

class pair {
    int values[2];

   public:
    pair(int v1, int v2) {
        values[0] = v1;
        values[1] = v2;
    }

    int& operator[](int id) { return values[id]; }
};

class monkey {
    int id;
    std::list<long> items;
    operation op;
    int opMembers[2];
    int testValue;
    monkey* targetMonkeyOnTrue;
    monkey* targetMonkeyOnFalse;
    long activity;

   public:
    monkey() : items(), activity(0) {}

    static void fromFile(std::fstream& file, std::vector<monkey*>& monkeys) {
        std::string buffer;
        std::list<pair> targetMonkeyIds;

        do {
            monkey* m = new monkey();
            getline(file, buffer);
            buffer.erase(0, 7);
            m->id = stoi(buffer);

            getline(file, buffer);
            buffer.erase(0, 18);
            std::istringstream ss(buffer);
            char separator;
            long item;
            do {
                ss >> item;
                m->items.push_back(item);
            } while (ss >> separator);

            getline(file, buffer);
            buffer.erase(0, 19);
            std::string members[2];
            char operation;
            ss = std::istringstream(buffer);
            ss >> members[0] >> operation >> members[1];
            if (operation == '+') {
                m->op = ADD;
            } else {
                m->op = MULTIPLY;
            }
            for (int i = 0; i < 2; i++) {
                if (members[i] == "old") {
                    m->opMembers[i] = 0;
                } else {
                    m->opMembers[i] = stoi(members[i]);
                }
            }

            getline(file, buffer);
            buffer.erase(0, 21);
            m->testValue = stoi(buffer);

            int onTrue, onFalse;
            getline(file, buffer);
            ss = std::istringstream(buffer);
            buffer.erase(0, 29);
            onTrue = stoi(buffer);
            getline(file, buffer);
            ss = std::istringstream(buffer);
            buffer.erase(0, 30);
            onFalse = stoi(buffer);

            targetMonkeyIds.push_back(pair(onTrue, onFalse));

            monkeys.push_back(m);
        } while (getline(file, buffer));

        int i = 0;
        for (auto targetIds : targetMonkeyIds) {
            monkeys[i]->targetMonkeyOnTrue = monkeys[targetIds[0]];
            monkeys[i]->targetMonkeyOnFalse = monkeys[targetIds[1]];
            i++;
        }
    }

    void execTurn(int part, long normalize) {
        while (!items.empty()) {
            long& item = items.front();

            long member1 = opMembers[0] == 0 ? item : opMembers[0];
            long member2 = opMembers[1] == 0 ? item : opMembers[1];

            switch (op) {
                case MULTIPLY:
                    item = member1 * member2;
                    break;
                case ADD:
                    item = member1 + member2;
                    break;
            }

            if (part == 1) {
                item = item / 3;
            } else {
                item = item % normalize;
            }

            monkey* target;
            if (item % testValue == 0) {
                target = targetMonkeyOnTrue;
            } else {
                target = targetMonkeyOnFalse;
            }

            target->items.splice(target->items.begin(), this->items, this->items.begin());

            activity++;
        }
    }

    long getActivity() { return activity; }
    int getTestValue() { return testValue; }
};

int partOne() {
    std::fstream inputFile;
    inputFile.open("input.txt", std::ios::in);

    std::vector<monkey*> monkeys;
    monkey::fromFile(inputFile, monkeys);

    inputFile.close();

    for (int round = 1; round <= 20; round++) {
        for (auto monkey : monkeys) {
            monkey->execTurn(1, 0);
        }
    }

    long highestActivity[2];
    highestActivity[0] = 0, highestActivity[1] = 0;
    for (auto monkey : monkeys) {
        long activity = monkey->getActivity();
        if (activity > highestActivity[0]) {
            if (activity > highestActivity[1]) {
                highestActivity[0] = highestActivity[1];
                highestActivity[1] = activity;
            } else {
                highestActivity[0] = activity;
            }
        }
    }

    long monkeyBusiness = highestActivity[0] * highestActivity[1];

    for (auto monkey : monkeys) {
        delete monkey;
    }

    return monkeyBusiness;
}

long partTwo() {
    std::fstream inputFile;
    inputFile.open("input.txt", std::ios::in);

    std::vector<monkey*> monkeys;
    monkey::fromFile(inputFile, monkeys);

    inputFile.close();

    long normalize = 1;
    for (auto monkey : monkeys) {
        normalize *= monkey->getTestValue();
    }

    for (int round = 1; round <= 10000; round++) {
        for (auto monkey : monkeys) {
            monkey->execTurn(2, normalize);
        }
    }

    long highestActivity[2];
    highestActivity[0] = 0, highestActivity[1] = 0;
    for (auto monkey : monkeys) {
        long activity = monkey->getActivity();
        if (activity > highestActivity[0]) {
            if (activity > highestActivity[1]) {
                highestActivity[0] = highestActivity[1];
                highestActivity[1] = activity;
            } else {
                highestActivity[0] = activity;
            }
        }
    }

    long monkeyBusiness = highestActivity[0] * highestActivity[1];

    for (auto monkey : monkeys) {
        delete monkey;
    }

    return monkeyBusiness;
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
