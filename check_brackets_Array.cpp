    #include <iostream>
    #include <fstream> 
    #include <sstream>
    #include <string>
    #include <stdexcept>
    #include <chrono>
    #include "DSStack.cpp"
    
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

    int matchBrackets(const char& b1, const char& b2) // returns values corresponding to the three possible actions
    {
        switch(b1) // returns 2 if matching, 1 if non-conflicting, and 0 if erroneous
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
    
    bool isBracket(const char& c) // determines if the passed char is a bracket
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
        auto start = std::chrono::high_resolution_clock::now(); // start the clock
        if(argc != 2) // check for proper # of arguments
            throw out_of_range("Incorrect number of file arguments: expects 1, received " + to_string(argc - 1));
        string checkFile = argv[1]; // store the input file from argument list
    
        ifstream inputFileStream; // prep for file parsing
        inputFileStream.open(checkFile);
        if(!inputFileStream.is_open())
            throw ifstream::failure("Unable to open input file: " + checkFile);
        DSStackArray<char> aStack = DSStackArray<char>(); // declare our objects and variables
        string inputLine;
        istringstream inputLineStream;
        int lineCount = 0;
        int errorCount = 0;
        char currChar;
        while(getline(inputFileStream, inputLine)) 
        {
            ++lineCount;
            removeCommentsAndStrings(inputLine); // cleans the input line of comments
            inputLineStream.clear(); // clear the last line before
            inputLineStream.str(inputLine); // inserting the new one
            while(inputLineStream >> currChar)
            {
                if(isBracket(currChar))
                {
                    if(aStack.isEmpty()) // handle no topChar case
                    {
                        aStack.push(currChar);
                    }
                    else
                    {
                        char topChar = aStack.getTop(); // get the top to compare to the currChar
                        int matchCheck = matchBrackets(topChar, currChar);
                        switch(matchCheck)
                        {
                            case 2: // matching brackets ('{' and '}')
                                aStack.pop();
                                break;
                            case 1: // no conlfict ('{' and '{', '{' and '(')
                                aStack.push(currChar);
                                break;
                            default: // conflict ('{' and ')')
                                // print debug info
                                cout << "Bracket Error detected in line " << lineCount << ", between brackets " << topChar << " and " << currChar << "\n";
                                cout << "Erroneous Line Content: " << inputLine << "\n"; 
                                ++errorCount;
                                break;
                        }
                    }
                }
            }
        }
        while(!aStack.isEmpty()) // this handles when brackets are left in the array due to certain errors
        {
            cout << "Bracket error involing a '" << aStack.pop() << "' somewhere in file\n"; 
            ++errorCount;
        }
        if(errorCount > 0)
            cout << "These brackets were in the stack at the end of the file, look for where they might be taking another brackets partner\n"; // best debug info I can offer
        auto stop = std::chrono::high_resolution_clock::now(); // stop the clock
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); // check the time
        cout << "Checking all files took " << duration.count() << " milliseconds\n\n";
        if(errorCount < 1) 
        {
            cout << checkFile << ": OK\n";
            return 0;
        }
        else
        {
            cout << checkFile <<  ": " << errorCount << " Bracket Mismatch(es) Detected \n";
            return 1;
        }
    }
    