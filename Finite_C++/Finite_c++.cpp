#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define MAX_STATES 1000
#define ASCII_SIZE 256
using namespace std;
// Function to compute the next state in the Finite Automaton
int getNextState(const string& pattern, int m, int state, int x) 
{
    // If the character matches the next character in the pattern, move to the next state
    if (state < m && x == pattern[state])
    {
        return state + 1;
	}
    int nextState, i;
    // Otherwise, find the longest prefix of the pattern that is also a suffix of the pattern[0...state-1]x
    for (nextState = state; nextState > 0; nextState--) 
	{
        if (pattern[nextState - 1] == x) 
		{
            for (i = 0; i < nextState - 1; i++) 
			{
                if (pattern[i] != pattern[state - nextState + 1 + i])
                    break;
            }
            if (i == nextState - 1)
                return nextState;
        }
    }
    return 0;
}
// Function to compute the Finite Automaton for the pattern
void computeFiniteAutomaton(const string& pattern, vector<vector<int> >& finiteAutomaton) 
{
    int m = pattern.size();
    int state, x;
    // Initialize the finite automaton with all zeros
    for (state = 0; state <= m; state++) 
	{
        for (x = 0; x < ASCII_SIZE; x++) 
		{
            finiteAutomaton[state][x] = 0;
        }
    }
    // Fill in the transitions for the finite automaton
    for (state = 0; state <= m; state++) 
	{
        for (x = 0; x < ASCII_SIZE; x++) 
		{	
            finiteAutomaton[state][x] = getNextState(pattern, m, state, x);
        }
    }
}
// Function to search for the pattern in the text using the Finite Automaton
void searchPattern(const string& text, const string& pattern) 
{
    int n = text.size();
    int m = pattern.size();
    int i, j, k;
    vector<vector<int> > finiteAutomaton(m + 1, vector<int>(ASCII_SIZE, 0));
    computeFiniteAutomaton(pattern, finiteAutomaton);
    int state = 0;
    for (j = 0; j < n; j++) 
	{
        state = finiteAutomaton[state][(int)text[j]];
        if (state == m) 
		{
            cout << "Pattern found at index " << j - m + 1 << endl;
        }
    }
    if(state!=m)
    {
    	cout<<"Pattern not found!!!"<<endl;
	}
}
int main() 
{
    // Open the text file
    ifstream textFile("text.txt");
    if (!textFile.is_open()) 
	{
        cerr << "Error opening text file" << endl;
        return 1;
    }

    // Open the pattern file
    ifstream patternFile("pattern.txt");
    if (!patternFile.is_open()) 
	{
        cerr << "Error opening pattern file" << endl;
        textFile.close();
        return 1;
    }

    // Read text from the file
    string text;
    getline(textFile, text);

    // Read pattern from the file
    string pattern;
    getline(patternFile, pattern);

    // Close the files
    textFile.close();
    patternFile.close();

    // Search for the pattern in the text
    searchPattern(text, pattern);

    return 0;
}

