#include <iostream>
#include <string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
map<pair<string, char>, string>transitions;
int numOfStates, numOfFinalStates, numOfAlphapets;
vector<string>states;
string startState;
vector<string>finalStates;
vector<char>alphapets;

void inputStates();
void inputStartState();
void inputFinalStates();
void inputAlphapets();
void inputTransitionTable();
bool check(string test);
bool ask();
int main()
{
    inputStates();
    inputStartState();
    inputFinalStates();
    inputAlphapets();
    inputTransitionTable();
    while (true)
    {
        bool exit = !ask();
        if (exit)return 0;
    }
}
void inputStates()
{
    while (true)
    {

        cout << "Enter number of states: ";

        cin >> numOfStates;
        if (numOfStates < 1)
        {
            cout << "please enter positive number\n";
            continue;
        }
        for (int i = 0;i < numOfStates;i++)
        {
            cout << "Enter state number " << i + 1 << " : ";
            string curState;
            cin >> curState;
            if (count(states.begin(), states.end(), curState))
            {
                cout << "this state is already exist, please enter new state\n";
                i--;
                continue;
            }
            states.push_back(curState);
        }
        break;
    }
}
void inputStartState()
{
    while (true)
    {
        cout << "Enter the start state: ";
        cin >> startState;
        if (!count(states.begin(), states.end(), startState))
        {
            cout << "this state is not exist, please enter valid state\n";
            continue;
        }
        break;
    }

}
void inputFinalStates()
{
    while (true)
    {
        cout << "Enter number of final states: ";
        cin >> numOfFinalStates;
        if (numOfFinalStates < 1)
        {
            cout << "please enter positive number\n";
            continue;
        }
        if (numOfFinalStates > numOfStates)
        {
            cout << "number of final states can't be greater "
                "than number of states, please enter valid number\n";
            continue;
        }
        break;
    }
    for (int i = 0;i < numOfFinalStates;i++)
    {
        cout << "Enter final state number " << i + 1 << " : ";
        string curState;
        cin >> curState;
        if (!count(states.begin(), states.end(), curState))
        {
            cout << "please enter valid state\n";
            i--;
            continue;
        }
        if (count(finalStates.begin(), finalStates.end(), curState))
        {
            cout << "this state is already exist as a final state, please enter new states\n";
            i--;
            continue;
        }
        finalStates.push_back(curState);
    }
}
void inputAlphapets()
{
    while (true)
    {
        cout << "Enter the number of alphapets in the target language: ";
        cin >> numOfAlphapets;

        if (numOfAlphapets < 1)
        {
            cout << "please enter positive number\n";
            continue;
        }
        break;
    }
    for (int i = 0;i < numOfAlphapets;i++)
    {
        cout << "Enter alphapet number " << i + 1 << ": ";
        char curAlphapet;
        cin >> curAlphapet;
        if (count(alphapets.begin(), alphapets.end(), curAlphapet))
        {
            cout << "this alphapet is already exist, please enter new alphapet\n";
            i--;
            continue;
        }
        alphapets.push_back(curAlphapet);
    }

}
void inputTransitionTable()
{
    cout << "Enter next state for each of these transitions\n";
    for (auto state : states)
    {
        for (auto alphapet : alphapets)
        {
            bool valid = false;
            {
                while (!valid)
                {
                    cout << state << "-- " << alphapet << " --> : ";
                    string nextState;
                    cin >> nextState;
                    if (!count(states.begin(), states.end(), nextState))
                    {
                        cout << "please enter valid state\n";
                        continue;
                    }
                    transitions[{state, alphapet}] = nextState;
                    valid = true;
                }
            }
        }
    }
}
bool check(string test)
{
    bool accepted = true;
    string curState = startState;
    for (auto curAlphapet : test)
    {
        if (!count(alphapets.begin(), alphapets.end(), curAlphapet))
        {
            accepted = false;
            break;;
        }
        curState = transitions[{curState, curAlphapet}];
    }
    return (accepted && count(finalStates.begin(), finalStates.end(), curState));
}
bool ask()
{

    int exit;
    cout << "If you want to check if a string of accepted or not in this language press 1,"
        "otherwise press 0 to end the program\n";

    cin >> exit;
    if (!exit)return false;
    else if (exit == 1)
    {
        cout << "Enter the string: ";
        string test;
        cin >> test;
        cout << "this string is ";
        cout << (check(test) ? "accepted" : "rejected");
        cout << " in this language\n";
    }
    else
    {
        cout << "unvalid input, please enter 0 or 1\n";
    }
    return true;
}


