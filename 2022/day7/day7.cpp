#include <cstring>
#include <fstream>
#include <iostream>
#include <list>

#define FILESYSTEM_STORAGE 70000000
#define FREE_SPACE_REQUIRED 30000000

class Node {
    std::string name;
    Node* parentDirectory;
    long size;
    std::list<Node*>* content;

   public:
    Node(std::string name, Node* parentDir, long size, bool isDir)
        : name(name), parentDirectory(parentDir), size(size) {
        if (isDir) {
            content = new std::list<Node*>();
        } else {
            content = NULL;
        }
    }

    void addFile(std::string name, long size) {
        Node* dir = this;
        content->push_back(new Node(name, dir, size, false));

        dir->size += size;
        while (dir->parentDirectory != NULL) {
            dir = dir->parentDirectory;
            dir->size += size;
        }
    }

    void addDirectory(std::string name) {
        Node* dir = this;
        content->push_back(new Node(name, dir, 0, true));
    }

    Node* changeDirectory(std::string name) {
        if (name == "..") return parentDirectory;
        for (Node* node : *content) {
            if (name == node->name) return node;
        }
        std::cout << this->name << ", " << name << std::endl;
        return NULL;
    }

    long getSize() { return size; }
    std::list<Node*>* getContent() { return content; }
    bool isDirectory() { return content != NULL; }

    std::string tree(int identation = 0, std::string* str = NULL) {
        std::string s;
        if (str == NULL) str = &s;
        for (int i = 0; i < identation; i++) str->append("  ");
        if (content != NULL) {
            str->append("- " + this->name + " (dir)" + std::to_string(this->size) + "\n");
            for (Node* node : *content) node->tree(identation + 1, str);
        } else {
            str->append("- " + this->name + " (file, size=" + std::to_string(this->size) + ")\n");
        }

        return s;
    }

    ~Node() { delete content; }
};

void getInput(Node* root) {
    std::fstream inputFile;
    char buffer[128];
    Node* currDir = root;
    inputFile.open("input.txt", std::ios::in);

    while (inputFile.getline(buffer, sizeof(buffer))) {
        if (buffer[0] == '$') {
            if (strncmp(buffer + 2, "cd", 2) == 0) {
                // change directory
                if (strcmp(buffer + 5, "/") == 0) {
                    currDir = root;
                } else {
                    currDir = currDir->changeDirectory(std::string(buffer + 5));
                }
            } else {
                // list
            }
        } else {
            if (strncmp(buffer, "dir", 3) == 0) {
                currDir->addDirectory(std::string(buffer + 4));
            } else {
                long size;
                char name[128];
                sscanf(buffer, "%ld %s", &size, name);
                currDir->addFile(std::string(name), size);
            }
        }
    }

    inputFile.close();
}

long sumSizes(Node* node) {
    long size = node->getSize();
    long sum = size <= 100000 ? size : 0;

    for (Node* child : *node->getContent()) {
        if (!child->isDirectory()) continue;
        sum += sumSizes(child);
    }

    return sum;
}

long getSmallestToFit(Node* node, long requiredSize) {
    long size = node->getSize();
    long currSmallest = size >= requiredSize ? size : FILESYSTEM_STORAGE;

    for (Node* child : *node->getContent()) {
        if (!child->isDirectory()) continue;
        size = getSmallestToFit(child, requiredSize);
        if (size < currSmallest) currSmallest = size;
    }

    return currSmallest;
}

long partOne() {
    Node root("/", NULL, 0, true);

    getInput(&root);

    return sumSizes(&root);
}

long partTwo() {
    Node root("/", NULL, 0, true);

    getInput(&root);

    return getSmallestToFit(&root, FREE_SPACE_REQUIRED - (FILESYSTEM_STORAGE - root.getSize()));
}

int main() {
    std::cout << "Part One: " << partOne() << std::endl;
    std::cout << "Part Two: " << partTwo() << std::endl;
}
