#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream infile("input.txt"); // input file
vector<char> input = {}; // vector to store line from file

void clearInputVector(){
    while (input.empty() == 0){
        input.pop_back();
    }
}

void nextLineAsVector(int firstChar){
    string line = "";
    getline (infile, line);
    if (firstChar != -1){
        line = static_cast<char>(firstChar) + line;
    }
    cout << endl << "DEBUG:\t" << line << endl;
    const char* cline = line.c_str();

    clearInputVector();
    for (int i = 0; i < line.length(); i++){
        input.push_back(cline[i]);
    }
}

// NOT WORKING? RECURSIVE EDITION
void ignoreBlockComment(){
    // search for "*/"
    int endLocation = -1; // index of '*' of comment end in vector. -1 means it hasnt been found
    for (int i = 0; i < (input.size() - 2); i++){
        cout << "DEBUG:\tSearching for block comment end..." << endl;
        if (input[i] == '*' && input[i + 1] == '/'){ // if current and next characters make "*/"
            endLocation = i;
        }
    }

    if (endLocation != -1 && endLocation != (input.size() - 2)){ // if end location has been found and isn't at the end of vector
        cout << "DEBUG:\tBlock comment end found! NOT at end of vector." << endl;
        vector<char> tempVector = {}; // create temporary vector to store everything after "*/"
        for (int i = (endLocation + 2); i < input.size(); i++){
            cout << "DEBUG:\tCreating temporary vector to hold remaining line:\t" << input[i] << endl;
            tempVector.push_back(input[i]);
        }
        clearInputVector(); // clear input vector and copy contents from temp vector
        for (int i = 0; i < tempVector.size(); i++){
            input.push_back(tempVector[i]);
        }
        return;
    }
    else if (endLocation != -1 && endLocation == (input.size() - 2)) { // if end location found AT end of vector
        cout << "DEBUG:\tBlock comment end found! at end of vector." << endl;
        nextLineAsVector(-1); // get the next line/vector
        return; // and return
    }
    else { // if "*/" wasn't found
        cout << "DEBUG:\tBlock comment end NOT found. Getting next line and trying again." << endl;
        nextLineAsVector(-1); // get the next line/vector
        ignoreBlockComment(); // recursively call function with next line/vector
        return; 
    }
}

// vector<char> ignoreBlockComment(vector<char> newInput, ifstream& infile){
//     // search for "*/"
//     int endLocation = -1; // index of '*' of comment end in vector. -1 means it hasnt been found
//     while (endLocation == -1){
//         for (int i = 0; i < (newInput.size() - 1); i++){
//             if (newInput[i] == '*' && newInput[i + 1] == '/'){ // if current and next characters make "*/"
//                 endLocation = i;
//             }
//         }
//         if (endLocation == -1){ // if it's still not found,
//             int ch = infile.get(); // silly thing to make nextLineAsVector work properly
//             newInput = nextLineAsVector(infile, ch); // call function to get next line/vector and try (loop) again
//         }
//     }
//     if (endLocation != (newInput.size() - 2)){ // if end location isn't at the end of vector
//         // create another new vector and store everything after "*/"
//         vector<char> newNewInput = {};
//         for (int i = endLocation + 2; i < newInput.size(); i++){
//             newNewInput.push_back(newInput[i]);
//         }
//         return newNewInput;
//     }
//     else /*if (endLocation != -1 && endLocation == (newInput.size() - 2))*/ { // if end location IS at end of vector
//         int ch = infile.get(); // silly thing to make nextLineAsVector work properly
//         return ( nextLineAsVector(infile, ch) ); // return the next line/vector
//     }
// }

int main() {
    enum class TokenType
    {
        Default,
        Keyword,
        Identifier,
        Number,
        Operator,
        Punctuation,
        Comment,
    };
    class LexAnalyzer
    {
    private:
        vector<char> input;
        int position;
            bool blockComment;


    public:
        LexAnalyzer(const vector<char>& inputVector)
        {
            input = inputVector;
            position = 0;
            blockComment = false;
        }
       bool getBlockComment()
       {
        return blockComment;
       }
        void advance()
        {
            position++;
        }
        int getPosition()
        {
            return position;
        }
        void resetPosition()
        {
            position = 0;
        }

        char peek()
        {
            if (position + 1 < input.size())
                return input[position + 1];

            return '\0';
        }

        char current()
        {
            if (position < input.size())
                return input[position];

            return '\0';
        }
       // void ignoreCommentBlock()
        //{
          //  while (inputRemaining() &&
            //    !(current() == '*' && peek() == '/'))
            //{
             //   advance();
            //}
            //if (inputRemaining())
            //{
             //   advance();
             //   advance();
            //}
      //  }
        // void ignoreCommentBlock()
        // {
        //     while (current() != '*' && peek() != '/')
        //     {
        //         if (inputRemaining())
        //         {
        //             advance();
        //         }
        //         else
        //         {
        //             blockComment = true;
        //             break;
        //         }
        //     }
        // blockComment = false;
        //     if (inputRemaining())
        //     {
        //         advance();
        //         advance();
        //     }
        
        // }
        void ignoreWhiteSpace()
        {
            while (inputRemaining() && current() == ' ')
            {
                advance();
            }
        }
        bool isDigit(char input)
        {
            if (input == '0')
                return true;
            else if (input == '1')
                return true;
            else if (input == '2')
                return true;
            else if (input == '3')
                return true;
            else if (input == '4')
                return true;
            else if (input == '5')
                return true;
            else if (input == '6')
                return true;
            else if (input == '7')
                return true;
            else if (input == '8')
                return true;
            else if (input == '9')
                return true;
            else
                return false;
        }
        bool isLetter(char input)
        {
            return (input >= 'a' && input <= 'z') ||
                (input >= 'A' && input <= 'Z');
        }
        bool isKeyword(string input)
        {
            return (input == "read" || input == "write");
        }

        bool inputRemaining()
        {
            return position < input.size();
        }
    };

    struct Token
    {
        TokenType type = TokenType::Default;
        string specificType = "";
    };

    
    int ch;
    while ((ch = infile.get()) != EOF){
        nextLineAsVector(ch);
            
        string number = "";
        string word = "";
        LexAnalyzer lexer(input);
        Token tkn;
        bool lineComment = false;
        //Loop processes 1 line from input file
        while (lexer.inputRemaining() && !lineComment)
        {
            char currentChar = lexer.current();
            switch (currentChar)
            {
            case ('+'):
                tkn.type = TokenType::Operator;
                tkn.specificType = "ADD";
                cout << "add token stored!";
                lexer.advance();


                break;
            case ('-'):
                tkn.type = TokenType::Operator;
                tkn.specificType = "SUB";
                cout << "sub token stored!";
                lexer.advance();
                break;

            case ('*'):
                tkn.type = TokenType::Operator;
                tkn.specificType = "MULT";
                cout << "mult token stored!";
                lexer.advance();;
                break;
            case ('/'):
                if (lexer.peek() == '/' || lexer.peek() == '*')
                {
                    tkn.type = TokenType::Comment;
                    if (lexer.peek() == '/')
                    {
                        lineComment = true;
                        cout << "remaining data in line ignored";
                        break;

                    }
                    if (lexer.peek() == '*') // BLOCK COMMENT START
                    {
                        // lexer.ignoreCommentBlock();
                        // cout << "block ignored!";
                        // if (lexer.getBlockComment())
                        // {
                        //     cout << "we are in a block comment! continue to next vector";
                        //     break;
                        // }

                        lexer.advance();
                        lexer.advance();

                        vector<char> tempVector = {}; // create temporary vector to store everything after "/*"
                        for (int i = lexer.getPosition(); i < input.size(); i++){
                            tempVector.push_back(input[i]);
                        }
                        clearInputVector(); // clear input vector and copy contents from temp vector
                        for (int i = 0; i < tempVector.size(); i++){
                            input.push_back(tempVector[i]);
                        }

                        ignoreBlockComment();
                        lexer.resetPosition();
                        cout << "DEBUG:\tBlock comment ignored!" << endl << "New position: " << lexer.getPosition() << endl;
                    }
                }
                else
                {
                    tkn.type = TokenType::Operator;
                    tkn.specificType = "DIV";
                    cout << "div token stored";
                    lexer.advance();

                }
                break;
            case (':'):
                if (lexer.peek() == '=')
                {
                    tkn.type = TokenType::Operator;
                    tkn.specificType = "ASSIGN";
                    cout << "assign token stored";
                    lexer.advance();
                    lexer.advance();
                }
                else
                {
                    cout << "unhandled case";
                    lexer.advance();
                }
                break;
            case ('('):
                tkn.type = TokenType::Punctuation;
                tkn.specificType = "LPAREN";
                cout << "lparen token stored";
                lexer.advance();
                break;
            case (')'):
                tkn.type = TokenType::Punctuation;
                tkn.specificType = "RPAREN";
                cout << "rparen token stored";
                lexer.advance();
                break;
            case ('.'):
                if (lexer.isDigit(lexer.peek()))
                {
                    number = ".";

                    lexer.advance();

                    while (lexer.isDigit(lexer.current()))
                    {
                        number += lexer.current();
                        lexer.advance();
                    }

                    tkn.type = TokenType::Number;
                    cout << number << " stored as token!";
                    number = "";
                    cout << " number cleared!";
                }
                else
                {
                    tkn.type = TokenType::Punctuation;
                    tkn.specificType = "PERIOD";
                    cout << "period stored!";
                    lexer.advance();
                }
                break;
            case (' '):
                lexer.ignoreWhiteSpace();
                break;
            default:
                if (lexer.isDigit(currentChar))
                {
                    bool hasDecimal = false;
                    while (lexer.isDigit(lexer.current()) ||
                        (lexer.current() == '.' && !hasDecimal))
                    {
                        if (lexer.current() == '.')
                        {
                            hasDecimal = true;
                        }
                        number += lexer.current();
                        lexer.advance();
                    }
                    tkn.type = TokenType::Number;
                    cout << number << " stored as token!\n";
                    number = "";
                    cout << "number cleared!";
                }
                else if (lexer.isLetter(currentChar))
                {
                    while (lexer.isLetter(lexer.current()) || lexer.isDigit(lexer.current()))
                    {
                        word += lexer.current();
                        lexer.advance();
                    }
                    if (lexer.isKeyword(word))
                    {
                        tkn.type = TokenType::Keyword;
                        if (word == "read")
                        {
                            tkn.specificType = "READ";
                            cout << "keyword read stored";

                        }
                        else if (word == "write")
                        {
                            tkn.specificType = "WRITE";
                            cout << "keyword write stored";
                        }
                        else
                        {
                            cout << "how did we get here";
                        }
                    }
                    else
                    {
                        tkn.type = TokenType::Identifier;
                        tkn.specificType = word;
                        cout << "identifier \"" << word << "\" stored!";
                    }
                    word = "";
                    cout << " word cleared!";

                }
            }
        }
    
}
    //We need a loop that will re-enter my loop while the file still has lines remaining
    //We need an output that actually stores the tokens
}
