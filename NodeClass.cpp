#include <iostream>
using namespace std;

class Node {
public:
    Node* letters[26];
    Node* parent;
    bool isEnd;

    Node() {
        for(int i = 0; i < 26; i++) {
            letters[i] = NULL;
        }
        parent = NULL;
        isEnd = true;
    }
};
