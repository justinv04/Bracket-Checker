#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctime>
#include "DSStack.cpp"

using namespace std;

int matchBrackets(const char& b1, const char& b2)
{
    switch(b1)
    {
        case '{': 
            return b2 == '}' ? 2 : (b2 == '{' || b2 == '(' || b2 == '[') ? 1 : 0;
        case '(':
            return b2 == ')' ? 2 : (b2 == '{' || b2 == '(' || b2 == '[') ? 1 : 0;
        case '[':
            return b2 == ']' ? 2 : (b2 == '{' || b2 == '(' || b2 == '[') ? 1 : 0;
        default:
            return 1;
    }
}

bool isBracket(const char& c)
{
    switch(c)
    {
        case '{':
        case '}':
        case '(':
        case ')':
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
    return false;
}

int main(int argc, char **argv)
{
    if(argc != 2)
        throw out_of_range("Incorrect number of file arguments: expects 1, received " + to_string(argc - 1));
    size_t startTime, endTime, runTime;
    string checkFile = argv[1];
    startTime = time(0);

    ifstream inputFileStream;
    inputFileStream.open("test_data/" + checkFile);
    if(!inputFileStream.is_open())
        throw ifstream::failure("Unable to open input file: " + checkFile);
    DSStackArray<char> aStack = DSStackArray<char>();
    string inputLine;
    istringstream inputLineStream;
    int lineCount = 0;
    char currChar;
    while(getline(inputFileStream, inputLine))
    {
        inputLineStream.clear();
        inputLineStream.str(inputLine);
        ++lineCount;
        while(inputLineStream >> currChar)
        {
            if(isBracket(currChar))
            {
                if(aStack.isEmpty())
                {
                    aStack.push(currChar);
                }
                else
                {
                    char topChar = aStack.getTop();
                    int matchCheck = matchBrackets(topChar, currChar);
                    switch(matchCheck)
                    {
                        case 2:
                            aStack.pop();
                            break;
                        case 1:
                            aStack.push(currChar);
                            break;
                        default:
                            cout << "Bracket Error detected in line " << lineCount << ", between brackets " << topChar << " and " << currChar << "\n";
                            cout << "Erroneous Line Content: " << inputLine << "\n";

                            endTime = time(0);
                            runTime = endTime - startTime;
                            cout << "Checking all files took " << runTime << " milliseconds" << endl;
                            return 1;
                    }
                }
            }
        }
    }
    endTime = time(0);
    runTime = endTime - startTime;
    cout << checkFile << ": OK\n";
    cout << "Checking all files took " << runTime << " milliseconds" << endl;
    return 0;
}
