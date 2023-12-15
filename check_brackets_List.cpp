#include <iostream>
#include <fstream>
#include <sstream>
#include <string>                   //      Identical to check_brackets_Array, except this uses a DSStackList, which uses a DSList
#include <stdexcept>                //      But the other file has the comments, so look there
#include <chrono>
#include "DSStack.cpp"
#include "DSList.cpp"

using namespace std;

void removeCommentsAndStrings(string& s) // processes lines for // comments
{
    int l = s.length();
    for(int i = 0; i < l; ++i)
    {
        if(s.at(i) == '/' && (s.at(i + 1) == '/' || s.at(i + 1) == '*')) // if there are comments in the string
        {
            if(s.at(i + 1) == '/')
                s = s.substr(0, i); // throw them and everything after them out
            else
            {
                int l2 = i + 1;
                while(s.at(l2) != '/')
                    l2++;
                s = s.substr(0, i) + s.substr(l2 + 1, l); // throw out everything in between the comments
            }
            return;
        }
            
        if(s.at(i) == '\'') // if there is a char
        {
            if(s.at(i) == '\\') // if it's a char with a backslash
                s = s.substr(0, i) + s.substr(i + 4, l); // remove it from the string
            else
                s = s.substr(0, i) + s.substr(i + 3, l);
            return;
        }

        if(s.at(i) == '"') // if there is a string 
        {
            int l2 = i + 1;
            while(s.at(l2) != '"')
                l2++;
            s = s.substr(0, i) + s.substr(l2 + 1, l); // remove all characters in the string
            return;
        }
    }
}

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
            return 0;
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
    string checkFile = argv[1];
    auto start = std::chrono::high_resolution_clock::now();

    ifstream inputFileStream;
    inputFileStream.open(checkFile);
    if(!inputFileStream.is_open())
        throw ifstream::failure("Unable to open input file: " + checkFile);

    DSStackList<char> lStack = DSStackList<char>();
    string inputLine;
    istringstream inputLineStream;
    int lineCount = 0;
    int errorCount = 0;
    char currChar;
    while(getline(inputFileStream, inputLine))
    {
        ++lineCount;
        removeCommentsAndStrings(inputLine);
        inputLineStream.clear();
        inputLineStream.str(inputLine);
        while(inputLineStream >> currChar)
        {
            if(isBracket(currChar))
            {
                if(lStack.isEmpty())
                {
                    lStack.push(currChar);
                }
                else
                {
                    char topChar = lStack.getTop();
                    int matchCheck = matchBrackets(topChar, currChar);
                    switch(matchCheck)
                    {
                        case 2:     // brackets match ('{' and '}')
                            lStack.pop();
                            break;
                        case 1:     // brackets do not conflict ('{' and '{', '{' and '(')
                            lStack.push(currChar);
                            break;
                        default:    // brackets do conflict ('}' and '}', '{' and ')')
                            cout << "Bracket Error detected in line " << lineCount << ", between brackets " << topChar << " and " << currChar << "\n";
                            cout << "Erroneous Line Content: " << inputLine << "\n";
                            ++errorCount;
                            break;
                    }
                }
            }
        }
    }
    while(!lStack.isEmpty())
        {
            cout << "Bracket error involing a '" << lStack.pop() << "' somewhere in file\n";
            ++errorCount;
        }
        if(errorCount > 0)
            cout << "These brackets were in the stack at the end of the file, look for where they might be taking another brackets partner\n\n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Checking all files took " << duration.count() << " milliseconds\n\n";
        if(errorCount < 1)
        {
            cout << checkFile << ": OK\n";
            return 0;
        }
        else
        {
            cout << checkFile <<  ": " << errorCount << " Bracket Mismatch(s) Detected \n";
            return 1;
        }
}