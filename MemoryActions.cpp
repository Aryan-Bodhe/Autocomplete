#include <iostream>
#include <fstream>
#include <vector>
#include "constants.cpp"
#include "NodeClass.cpp"
using namespace std; 

// static Node* &globalRoot;
// vector<string> wordList;

void addWord(Node *&root, string &word, int index)
{
    if (index == word.length())
    {
        return;
    }

    int letterIndex = word[index] - 'a';

    if (root->letters[letterIndex] == NULL)
    {
        root->letters[letterIndex] = new Node();
        root->isEnd = false;
        (root->letters[letterIndex])->parent = root;
    }
    // cout << "Added" << endl;
    addWord(root->letters[letterIndex], word, index + 1);
}

void addWordToMemory(Node *&root, string &word)
{
    if (word.empty())
    {
        return;
    }

    addWord(root, word, 0);
    // wordList.push_back(word);
}

bool processWord(string& word) {
    int n = word.length();
    for(int i = 0; i < n; i++) {
        if(word[i] < 'a' || word[i] > 'z') 
            return false;
        i = tolower(i);
    }
    return true;
}

void initialiseMemoryWithWordbase(Node* &root)
{
    root = new Node();

    ifstream wordbase(WORDBASE_FILE);
    string word;

    if(!wordbase.is_open()) {
        cout << WORDBASE_NOT_FOUND_ERROR << endl;
        return;
    }
    
    while(getline(wordbase, word)) {
        processWord(word);
        addWordToMemory(root, word);
    }

    // for(auto i : wordList) {
    //     cout << i << endl;
    // }

    wordbase.close();
}

void returnSuggestions(Node* &root, string typedWord, int& suggestions, vector<string>& results) {
    if(root == NULL) {
        return;
    }
    bool allNull = true;
    for(int i = 0; i < 26; i++) {
        if(root->letters[i] != NULL) {
            allNull = false;
            typedWord.push_back('a'+ i);
            returnSuggestions(root->letters[i], typedWord, suggestions, results);
            typedWord.pop_back();
        }
        if(suggestions == SUGGESTION_COUNT) {
            return;
        }
    }
    if(allNull) {
        results.push_back(typedWord);
        suggestions++;
    }
    return;
}

vector<string> getSuggestions(Node* &root, string typedWord) {

    Node* node = root;
    vector<string> results; 
    int i = 0;
    int sugCount = 0;

    for(int i = 0; i < typedWord.length(); i++) {
        if(node == NULL)   
            return results;
        node = node->letters[typedWord[i] - 'a'];
    }
    returnSuggestions(node, typedWord, sugCount, results);
    return results;
}

// update: return the results vector to use 
vector<string> printMemorySuggestions(Node* &root, string curr) //returns max first 5 memory suggestions
{
    Node* node = root;
    vector<string> results;
    int suggestionCount = SUGGESTION_COUNT;

    if(root == NULL) {
        cout << EMPTY_TREE_ERROR << endl;
        return results;
    }

    results = getSuggestions(node, curr);

    cout << "\033[32m";
    for(auto suggestedWord : results) {
        cout << suggestedWord << endl;
    }
    cout << "\033[0m";
    return results;
}
