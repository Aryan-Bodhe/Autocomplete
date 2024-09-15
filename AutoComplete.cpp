#include <iostream>
#include <conio.h>
#include "MemoryActions.cpp"
using namespace std;

void printResultList(vector<string>& results, int resultIndex) {
    cout << "\033[32m";
    for (int i = 0; i < SUGGESTION_COUNT; i++)
    {
        if(i == resultIndex) {
            cout << "->";
        }
        cout << results[i] << endl;
    }
    cout << "\033[0m";
}

void inputFromUserAndSuggest(Node *&root)
{
    system("cls");
    cout << "\033[0m";
    string currWord = "";
    string selectedSuggestion = "";
    vector<string> results;
    char c;
    bool isValid = true;
    int resultIndex = -1;

    cout << USER_TEXT_PROMPT << endl;
    do
    {
        c = getch();
        if(c == ENTER_KEY) {
            // if(!selectedSuggestion.empty())
            //     currWord = selectedSuggestion;
            resultIndex = 0;
            break;
        }
        if(c == TAB_KEY) {
            system("cls");
            cout << USER_TEXT_PROMPT << endl;
            currWord = selectedSuggestion;
            cout << currWord << endl;
            results = printMemorySuggestions(root, currWord);
            continue;
        }
        // Handle arrow keys
        if(c == ARROW_KEY_PREFIX) {
            c = getch();
            if (c == KEY_DOWN)
            {
                system("cls");
                cout << USER_TEXT_PROMPT << endl;
                if(resultIndex < 4) {
                    resultIndex++;
                }
                selectedSuggestion = results[resultIndex];
                cout << currWord << endl;
                printResultList(results, resultIndex);
                continue;
            }
            else if (c == KEY_UP)
            {
                system("cls");
                cout << USER_TEXT_PROMPT << endl;
                if (results.empty()) {
                    cout << "empty" << endl;
                    continue;
                }
                if (resultIndex > 0)
                {
                    resultIndex--;
                }
                selectedSuggestion = results[resultIndex];
                cout << currWord << endl;
                printResultList(results, resultIndex);
                continue;
            }
            else if (c == KEY_RIGHT || c == KEY_LEFT)
                continue;
        }

        // Handle backspace input
        else if (c == BACKSPACE_KEY)
        {
            system("cls");
            cout << USER_TEXT_PROMPT << endl;
            resultIndex = -1;
            if (!currWord.empty())
            {
                currWord.pop_back();
                cout << currWord << endl;
                if (!currWord.empty())
                    results = printMemorySuggestions(root, currWord);
            }
            continue;
        }

        // Handle standard append
        c = tolower(c);
        currWord.push_back(c);
        resultIndex = -1;

        system("cls");
        cout << USER_TEXT_PROMPT << endl;
        cout << currWord << endl;

        // check for valid range of characters and suggest words
        if ('a' <= c && c <= 'z' && isValid)
        {
            results = printMemorySuggestions(root, currWord);
        }
        else
        {
            isValid = false;
        }

    } while (c != ENTER_KEY);

    cout << endl;
    cout << "You have entered : " << currWord << endl;
}

int main()
{
    Node *root = NULL;
    initialiseMemoryWithWordbase(root);
    inputFromUserAndSuggest(root);
}