#include <iostream>
#include <conio.h>
#include "MemoryActions.cpp"
using namespace std;

void inputFromUserAndSuggest(Node* &root) {
    system("cls");
    string currWord;
    // vector<string> results;
    char c;
    bool isValid = true;

    cout << USER_TEXT_PROMPT << endl;
    do {
        c = getch();
        c = tolower(c);
        if(c == '\b') {
            system("cls");
            cout << USER_TEXT_PROMPT << endl;
            if(!currWord.empty()) {
                currWord.pop_back();
                cout << currWord << endl;
                if(!currWord.empty())
                    printMemorySuggestions(root, currWord);
            }
            // cout << currWord << endl;
            continue;
        }
        currWord.push_back(c);
        system("cls");
        cout << USER_TEXT_PROMPT << endl;
        cout << currWord << endl;

        //check for valid range of characters
        if('a' <= c && c <= 'z' && isValid) {
            printMemorySuggestions(root, currWord);   
        }
        else {
            isValid = true;
        }
    }
    while (c != '\r');
}

int main() {
    Node* root = NULL;
    initialiseMemoryWithWordbase(root);
    inputFromUserAndSuggest(root);
}