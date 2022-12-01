#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct binaryTreeNode {
    binaryTreeNode* r;
    binaryTreeNode* l;
    int value;

    binaryTreeNode(int v) : r(NULL), l(NULL), value(v) {}
};

void addToTree(const string& s, binaryTreeNode* node) {
    for (char c : s) {
        node->value++;
        if (c == '1') {
            if (node->r == NULL) {
                node->r = new binaryTreeNode(0);
            }
            node = node->r;
        } else {
            if (node->l == NULL) {
                node->l = new binaryTreeNode(0);
            }
            node = node->l;
        }
    }
}

int getIndex(binaryTreeNode* node, bool mostCommon) {
    int value = 0;

    while (node->r != NULL || node->l != NULL) {
        value *= 2;
        if (node->l == NULL || (node->r != NULL && ((mostCommon && node->r->value >= node->l->value)
                                                    || !mostCommon && node->r->value < node->l->value))) {
            value++;
            node = node->r;
        } else {
            node = node->l;
        }
    }

    return value;
}

int lifeSupportRating() {
    int oxigen = 0, co2 = 0;
    binaryTreeNode root(0);
    string str;

    while (getline(cin, str)) {
        addToTree(str, &root);
    }

    oxigen = getIndex(&root, true);
    co2 = getIndex(&root, false);

    return oxigen * co2;
}

int main() {
    cout << lifeSupportRating() << endl;

    return 0;
}