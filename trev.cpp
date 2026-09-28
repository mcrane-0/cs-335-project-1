#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

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
        void ignoreCommentBlock()
        {
            blockComment = false;
            while (current() != '*' && peek() != '/')
        {
            if (inputRemaining())
            {
                advance();
            }
            else
            {
                blockComment = true;
                break;
            }
        }
            if (inputRemaining())
            {
                advance();
                advance();
            }
        
        }
        void ignoreWhiteSpace()
        {
            while (inputRemaining() && current() == ' ')
            {
                    position++;
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

    //INSERT method to read input file here
    vector<char> input = { '+', '-', '*', '/', '1', '2', '3', '.', '3', '/', '*', 'l', '*', '/', '*', 'r', 'e', 'a', 'd', '+','a','1', ' ',' ', 'a', ' ', '1', '/', '/', 'o'};
    string number = "";
    string word = "";
    LexAnalyzer lexer(input);
    Token tkn;
    bool lineComment = false;
    while (lexer.getBlockComment())
    {
        lexer.ignoreCommentBlock();
    }
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
                if (lexer.peek() == '*')
                {
                    lexer.ignoreCommentBlock();
                    cout << "block ignored!";

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
                    cout << "identifier \" " << word << "\" stored!";
                }
                word = "";
                cout << " word cleared!";

            }
        }
    }
    //We need a loop that will re-enter my loop while the file still has lines remaining
    //We need an output that actually stores the tokens
}
